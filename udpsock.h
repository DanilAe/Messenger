#ifndef UDPSOCK_H
#define UDPSOCK_H

#include <QObject>
#include <iostream>
#include <QUdpSocket>
#include <QMap>
#include <QStringList>
#include <iomanip>
#include <QDateTime>
#include <QVector>
#include <message.h>

class UdpSock : public QObject
{
		Q_OBJECT

		QUdpSocket* m_pudp;

		QHostAddress last = QHostAddress::LocalHost;

		QHostAddress local = QHostAddress::LocalHost;

		quint16 port_last = 8080;

		QString m_usrName;		

		Q_PROPERTY(QString usrName READ usrName WRITE setUsrName)

		Q_PROPERTY(QString ipAddr READ ipAddr WRITE setIpAddr)

		Q_PROPERTY(QString localHost READ localHost)

	public:

		explicit UdpSock(QObject *parent = nullptr);

		QString localHost()
		{ return local.toString(); }

		Q_INVOKABLE void sendData(QString data)
		{ this->sendData(QByteArray().append(data), last, port_last); }

		void sendData(QByteArray data, QHostAddress reciever, quint16 recieverPort);

		QString ipAddr()
		{ return last.toString(); }

		QString usrName()
		{ return m_usrName; }

		void setUsrName(QString usrName_)
		{ m_usrName = usrName_; }

		void setIpAddr(QString other)
		{
			last = QHostAddress(other);
		}

	signals:

		void newmessage(QString usrName, QString msgText, QString msgDate, QString ipAddress);

	public slots:

		void onNewMessage();
};

#endif // UDPSOCK_H
