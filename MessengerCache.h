#ifndef ENUMS_H
#define ENUMS_H

#include <QObject>
#include "message.h"

class UserInfo : public QObject
{
		Q_OBJECT

		QString m_userName;

		QString m_lastUser;

	public:

		Q_PROPERTY(QString unkown READ unkown)

		Q_PROPERTY(QString usrName READ userName WRITE setUserName)

		Q_PROPERTY(QString lastUser READ lastUser WRITE setLastUser)

		explicit UserInfo(QObject* parent = nullptr) : QObject(parent)
		{

		}

		QString unkown()
		{ return "unkown";}

		void setUserName(QString name)
		{ this->m_userName = name; }

		QString userName()
		{ return this->m_userName;}

		void setLastUser(QString name)
		{ this->m_lastUser = name; }

		QString lastUser()
		{ return this->m_lastUser; }
};

class History : public QObject
{
		Q_OBJECT

		typedef QPair<QString, QVector<Message*>> chat;

		QVector<chat>* chats;

	public:

		explicit History(QObject* parent = nullptr) : QObject(parent)
		{			
			chats = new QVector<chat>();
		}

		Q_INVOKABLE void addMessage(QString usrName__, QByteArray data)
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

		Q_INVOKABLE void getMessages(QString chatIp)
		{
			QVector<Message*> messages;
			for(int i = 0; i < chats->size(); i++)
			{
				if(chats->at(i).first == chatIp)
				{
					messages =  chats->at(i).second;
				}
			}
			emit clear();
			for(Message* msg : messages)
			{
				emit getmessage(msg->usrName(), msg->msgText(), msg->msgDate());
				qDebug() << "---------" << chatIp.toStdString().c_str() << "--------";
				qDebug() << "usrName:\t" << msg->usrName();
				qDebug() << "msgText:\t" << msg->msgText();
				qDebug() << "msgDate:\t" << msg->msgDate();
				qDebug() << "----------------------------";
			}
		}

	signals:

		void getmessage(QString usrName, QString msgText, QString msgDate);

		void clear();
};

#endif // ENUMS_H
