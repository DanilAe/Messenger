import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import my.program.udpSock 1.0
import my.porgram.message 1.0
import "JsSource.js" as JsEngine
import my.program.cache.history 1.0
import my.program.cache.userInfo 1.0

ApplicationWindow {
    visible: true
    width: 940
    height: 720
    title: qsTr("Messenger")
    property int chat: -1

    History {
        id: history
        onClear: msgView.listModel.clear()
        onGetmessage: JsEngine.add(usrName, msgText, msgDate)
    }

    UserInfo {
        id: userInfo
    }

    UdpSocket {
        id: socket
        onNewmessage: JsEngine.newMessage(usrName, msgText, msgDate, ipAddress)
    }
    MessageView {
        id: msgView
        anchors.rightMargin: 0
        anchors.fill: parent
    }
}

