import QtQuick 2.0

import QtQuick.Controls 1.4

Item {
    Component {
        id: columnComponent
        TableViewColumn {
            width: 150
        }
    }


    TableView {
        id: logViewer

        property int activeColumn: 0
        property var titles: LogModel.titles
        property var curTitles: {
            var t = []
            for (var i = 0; i < columnCount; i++) {
                t.push(getColumn(i).title);
            }
            return t;
        }

        onTitlesChanged: {
            for (var i = 0; i < titles.length; i++) {
                if (curTitles.indexOf(titles[i]) === -1) {
                    var column = addColumn(columnComponent);
                    column.title = titles[i];
                    column.role = titles[i];
                }
            }

            for (i = curTitles.length - 1; i >= 0; i--) {
                if (titles.indexOf(curTitles[i]) === -1) {
                    removeColumn(i);
                }
            }
        }

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
                        LogModel.orderBy(styleData.value)
                    }
                }
            }
        }
    }
}
