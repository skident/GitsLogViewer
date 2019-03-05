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


    Rectangle {
        id: topPanel

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 40

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


        Button {
            anchors.right: parent.right

            text: "Change"
            checkable: true

            onCheckedChanged: {
                if (text === "Change") {
                    text = "Apply";

                    logView.refresh();
                    logView.editMode = true;

                } else {
                    text = "Change"
                    logView.apply();
                    logView.editMode = false;
                }
            }
        }
    }

    LogView {
        id: logView

        anchors.top: topPanel.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
