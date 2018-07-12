import QtQuick 2.0
import QtQuick.Controls 2.2
import "JsSource.js" as JsEngine

Item {
    property alias statusText: statusText.text
    property ListModel listModel: model
    property ListModel listModelR: model1
    Rectangle {
        id: leftPanel
        width: 400
        height: parent.height
        ListView {
            id: vi
            anchors.fill: parent
            model: model1
            delegate: delegate_1

        }
        Component {
            id: delegate_1
            Rectangle {
                width:  vi.width
                height: 40
                border.width: 1
                property int id: chatId
                property string ipAddr: ip
                Row {
                    y: 5
                    x: 5
                    Text {
                        anchors.fill: parent
                        textFormat: Text.PlainText
                        text: usrName
                        color: "gray"
                    }
                }
                Row {
                    y: 20
                    x: 20
                    Text {
                        anchors.fill: parent
                        textFormat: Text.PlainText
                        text: msgText
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(ip != "")
                        {
                            if(usrName != JsEngine.lastUsr)
                            {
                                JsEngine.changeChat(chatId, ip, usrName)
                            }
                        }
                    }
                }
            }
        }
        ListModel {
            id: model1
        }
    }
    Rectangle {
        id: rightPanel
        x: 400
        width: parent.width - 400
        height:  parent.height
        Rectangle {
            id: upPanel
            width: parent.width
            height: 50
            border.color: "black"
            border.width: 1
            color: "#1faee9"
            z: 10
            TextField {
                id: txtIp
                placeholderText: "The Ip of the source"
                color: "black"
                font.bold: true
                width: 200
                height: 30
                y: 10
                x: 10
            }
            Button {
                width: 35
                height: 30
                x: 225
                y: 10
                text: "Ok"
                onClicked: {
                    if(m_sock.ipAddr !== txtIp.text)
                    {
                        m_sock.ipAddr = txtIp.text
                        model.clear()
                        chat++
                    }
                }
            }
            Label {
                id: statusText
                x: 270
                y: 20
            }
        }
        Rectangle {
            y: 50
            height: parent.height - upPanel.height - panel.height
            width: parent.width
            border.width: 1
            ListView {
                id: view
                delegate: m_delegate
                model: model
                anchors.fill: parent
            }
        }
        ListModel {
            id: model
        }
        Component {
            id: m_delegate
            Row {
                spacing: 10
                Rectangle {
                    border.color: "light gray"
                    border.width: 1
                    width: view.width
                    height: txt.contentHeight + 30
                    Text {
                        id: txt
                        y: 16
                        x: 5
                        text: msgText
                        textFormat: Text.PlainText
                    }
                    Text {
                        id: txtN
                        text: usrName
                        color: "gray"
                        textFormat: Text.PlainText
                        x: 5
                        y: 3
                        font.pixelSize: 11
                    }
                    Text {
                        id: dateText
                        text: msgDate
                        textFormat: Text.PlainText
                        x: parent.width - contentWidth - 4
                        y: parent.height - contentHeight - 2
                        font.pixelSize: 10
                        color: "Gray"
                    }
                }
            }
        }
        Rectangle {
            color: "light gray"
            height: 120
            width: parent.width
            y: parent.height - 120
            x: 0
            id: panel
            Rectangle {
                x: 5
                radius: 5
                width: parent.width - 90
                height: parent.height - 10
                anchors.verticalCenter: parent.verticalCenter
                TextArea {
                    id: textInput
                    anchors.centerIn: parent
                    textFormat: Text.PlainText
                    width: parent.width - 10
                    height:  parent.height - 10
                }
            }
            Button {
                id: button
                text: "Send"
                width: 60
                height: parent.height - 20
                anchors.verticalCenter: parent.verticalCenter
                x: parent.width - 70
                onClicked:  {
                    if(textInput.text != "")
                    {
                        JsEngine.send(textInput.text.trim())
                        textInput.text = ""
                    }
                }
            }
        }
    }
}
