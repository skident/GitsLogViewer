import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Gits LogViewer")


    Item {
        id: downloadFileDropArea

        anchors.fill: parent
        z: parent.z + 100

        Rectangle {
            id: dropAreaBg

            anchors.fill: parent
            color: "grey"
            opacity: 0.5

            visible: false
        }

        Item {
            anchors.fill: parent

            DropArea {
                anchors.fill: parent

                onEntered: {
                    console.log("Entered");
                    dropAreaBg.visible = true;
                }

                onExited: {
                    console.log("Exited")
                    dropAreaBg.visible = false;
                }

                onDropped: {
                    console.log("Dropped ", drop.text)
                    AppController.openFile(drop.text)
                    dropAreaBg.visible = false;
                }
            }
        }
    }


    TableView {
        id: logViewer

        property int activeColumn: 0

        anchors.fill: parent

        model: LogModel


        headerDelegate: Rectangle {
            height: 20
            color: styleData.column === logViewer.activeColumn
                   ? "brown"
                   : "grey"

            Rectangle {
                id: separator

                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 1
                anchors.topMargin: 1
                width: 1
                color: "#333"
            }

            Text {
                text: styleData.value
                color: "#CFF"
                width: parent.width
                height: parent.height
                font.pointSize: 18
                minimumPointSize: 3
                fontSizeMode: Text.Fit
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Connections {
                target: styleData
                onPressedChanged: {
                    if (styleData.pressed) {
                        logViewer.activeColumn = styleData.column
                        LogModel.orderBy(styleData.column)
                    }
                }
            }
        }

        TableViewColumn {
            role: "timestamp"
            title: "Timestamp"
        }

        TableViewColumn {
            role: "threadId"
            title: "Thread ID"
        }

        TableViewColumn {
            role: "severity"
            title: "Severity"
        }

        TableViewColumn {
            role: "message"
            title: "Message"
        }
    }
}
