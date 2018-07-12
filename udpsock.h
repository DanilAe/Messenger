#ifndef UDPSOCK_H
#define UDPSOCK_H

#include <QObject>
#include <iostream>
#include <QUdpSocket>
#include <QMap>
#include <QStringList>
#include <iomanip>
#include <QVector>
#include <message.h>

class UdpSock : public QObject
{
		Q_OBJECT

		typedef QPair<QString, QVector<Message*>> chat;

		QUdpSocket* m_pudp;

		QHostAddress last = QHostAddress::LocalHost;

		quint16 port_last = 8080;

		QString m_usrName;

		QVector<chat>* chats;

		Q_PROPERTY(QString usrName READ usrName WRITE setUsrName)

		Q_PROPERTY(QString ipAddr READ ipAddr WRITE setIpAddr)

	public:
		Q_INVOKABLE void sendData(QString data)
		{ this->sendData(QByteArray().append(data), last, port_last); }

		Q_INVOKABLE void getMessages(QString chatName);

		explicit UdpSock(QObject *parent = nullptr);

		void sendData(QByteArray data, QHostAddress reciever, quint16 recieverPort);

		Q_INVOKABLE void addMessage(QString usrName__, QByteArray data);

		QString ipAddr()
		{ return last.toString(); }

		QString usrName()
		{ return m_usrName; }

		void setUsrName(QString usrName_)
		{ m_usrName = usrName_; }

		void setIpAddr(QString other)
		{ last = QHostAddress(other); }

	signals:
		void newmessage(QString usrName, QString msgText, QString msgDate, QString ipAddress);

		void getmessage(QString usrName, QString msgText, QString msgDate);

		void clear();

	public slots:
		void onNewMessage();
};

#endif // UDPSOCK_H
