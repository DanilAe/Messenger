#include "udpsock.h"

UdpSock::UdpSock(QObject *parent) : QObject(parent)
{
	chats = new QVector<chat>();
	m_pudp = new QUdpSocket();
	m_pudp->bind(QHostAddress::Any, 8080);
	connect(m_pudp, SIGNAL(readyRead()), this, SLOT(onNewMessage()));
}

void UdpSock::onNewMessage()
{
	QByteArray data;
	QHostAddress addr;
	data.resize(m_pudp->pendingDatagramSize());
	m_pudp->readDatagram(data.data(), data.size(), &addr);
	Message* msg = new Message(data);
	addMessage(msg->usrName(), data);
	qDebug() << "Read: \n" << msg->toString().toStdString().c_str();
	QString usrName_ = msg->usrName();
	QString msgText_ = msg->msgText();
	QString msgDate_ = msg->msgDate();
	if(addr != QHostAddress::LocalHost)
		emit newmessage(usrName_,msgText_,msgDate_, addr.toString());
}

void UdpSock::sendData(QByteArray data, QHostAddress reciever, quint16 recieverPort)
{
	Message* msg = new Message(data);
	qDebug() << "Send to " << reciever.toString() << ":" << recieverPort << '\n' << msg->toString().toStdString().c_str();
	if(reciever != QHostAddress::LocalHost)
		m_pudp->writeDatagram(data, reciever, recieverPort);
}

void UdpSock::addMessage(QString usrName__, QByteArray data)
{
	Message* msg = new Message(data);
	bool contains;
	int index;
	for(int i = 0; i < chats->size(); i++)
	{
		if(chats->at(i).first == usrName__)
		{
			contains = true;
			index = i;
			break;
		}
	}
	if(contains)
	{
		chat ch;
		ch.first = usrName__;
		ch.second = chats->at(index).second;
		ch.second.push_back(msg);
		chats->removeAt(index);
		chats->push_back(ch);
	}
	else
	{
		chat ch;
		ch.first = usrName__;
		ch.second.push_back(msg);
		chats->push_back(ch);
	}
}

void UdpSock::getMessages(QString chatName)
{
	QVector<Message*> messages;
	for(int i = 0; i < chats->size(); i++)
	{
		if(chats->at(i).first == chatName)
		{
			messages =  chats->at(i).second;
		}
	}
	emit clear();
	for(Message* msg : messages)
	{
		emit getmessage(msg->usrName(), msg->msgText(), msg->msgDate());
	}
}
