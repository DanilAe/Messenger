#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "udpsock.h"
#include "message.h"
#include "MessengerCache.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QCoreApplication::setApplicationName("Messenger");
	QCoreApplication::setApplicationVersion("1.0.0");
	QCoreApplication::setOrganizationName("Danil");

	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	qmlRegisterType<Message>("my.porgram.message", 1, 0, "Message");
	qmlRegisterType<UdpSock>("my.program.udpSock", 1, 0, "UdpSocket");
	qmlRegisterType<History>("my.program.cache.history", 1, 0, "History");
	qmlRegisterType<UserInfo>("my.program.cache.userInfo", 1, 0, "UserInfo");
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;
	return app.exec();
}
