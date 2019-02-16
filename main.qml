import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Gits LogViewer")


    FileDropArea {
        anchors.fill: parent
    }


    LogView {
        anchors.fill: parent
    }

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 20

        Row {
            TextField {
                id: regex
            }

            Button {
                text: "Change regex"
                onClicked: {
                    AppController.setRegex(regex.text)
                }
            }
        }
    }
}
