#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

class Message : public QObject
{
		Q_OBJECT
		QJsonDocument doc;
	public:
		Q_PROPERTY(QString usrName READ usrName WRITE setUsrName)
		Q_PROPERTY(QString msgText READ msgText WRITE setMsgText)
		Q_PROPERTY(QString msgDate READ msgDate WRITE setMsgDate)

		explicit Message(QObject *parent = nullptr)
		{
			doc.object().insert("msgDate", "");
			doc.object().insert("msgText", "");
			doc.object().insert("usrName", "");
			doc.object().insert("key", "");
		}

		Message(Message &other)
		{
			doc = QJsonDocument::fromJson(QByteArray().append(other.toString()));
		}

		Message(QByteArray data,QObject *parent = nullptr)
		{
			doc = QJsonDocument::fromJson(data);
		}

		QString key()
		{
			return this->doc.object().value("key").toString();
		}

		QString usrName()
		{
			return this->doc.object().value("usrName").toString();
		}

		QString msgText()
		{
			return this->doc.object().value("msgText").toString();
		}

		QString msgDate()
		{
			return this->doc.object().value("msgDate").toString();
		}

		void setUsrName(QString usrName_)
		{
			this->doc.object()["usrName"] = usrName_;
		}

		void setMsgText(QString msgText_)
		{
			this->doc.object()["msgText"] = msgText_;
		}

		void setMsgDate(QString msgDate_)
		{
			this->doc.object()["msgDate"] = msgDate_;
		}

		QString toString()
		{
			return this->doc.toJson(QJsonDocument::Indented);
		}
};

#endif // MESSAGE_H
