 #include "udpsock.h"

UdpSock::UdpSock(QObject *parent) : QObject(parent)
{
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
	if(reciever != QHostAddress::LocalHost)
	{
		m_pudp->writeDatagram(data, reciever, recieverPort);
		qDebug() << "Sent to " << reciever.toString() << ":" << recieverPort << '\n' << msg->toString().toStdString().c_str();
	}
}
