import QtQuick 2.0

Item {
    z: parent.z + 100

    Item {
        id: downloadFileDropArea

        anchors.fill: parent

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
}
