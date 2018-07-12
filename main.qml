import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import my.program.udpSock 1.0
import my.porgram.message 1.0
import "JsSource.js" as JsEngine

ApplicationWindow {
    visible: true
    width: 940
    height: 720
    title: qsTr("Messenger")
    property int chat: -1
    UdpSocket {
        id: m_sock
        onNewmessage: JsEngine.newMessage(usrName, msgText, msgDate, ipAddress)
        onGetmessage: JsEngine.add(usrName, msgText, msgDate)
        onClear: msgView.listModel.clear()
    }
    MessageView {
        id: msgView
        anchors.rightMargin: 0
        anchors.fill: parent
    }
}

