import QtQuick 2.0

import QtQuick.Controls 1.4

Item {
    property alias editMode: editableTitles.visible


    function renewColumns() {
        for (var i = logViewer.columnCount - 1; i >= 0; i--) {
            logViewer.removeColumn(i);
        }

        for (var i = 0; i < LogModel.titles.length; i++) {
            var column = logViewer.addColumn(columnComponent);
            column.title = LogModel.titles[i];
            column.role = LogModel.titles[i];
        }
    }

    // apply titles changes
    function apply() {
        var map = {};
        for (var i = 0; i < repeater.count; i++) {
            map[logViewer.getColumn(i).role] = repeater.itemAt(i).text;
        }
        LogModel.updateTitles(map);
    }

    function refresh() {
        for (var i = 0; i < logViewer.columnCount; i++) {
            repeater.itemAt(i).text = logViewer.getColumn(i).title;
        }
    }

    Component {
        id: columnComponent
        TableViewColumn {
            width: 150
        }
    }


    TableView {
        id: logViewer

        property int activeColumn: 0

        anchors.fill: parent

        model: LogModel

        Row {
            id: editableTitles

            anchors.top: parent.top
            visible: false

            Repeater {
                id: repeater

                model: logViewer.columnCount
                delegate: TextField {
                    width: logViewer.getColumn(modelData).width
                    height: logViewer.getColumn(modelData).height
                }
            }

            z: parent.z + 1
        }


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

    Connections {
        target: LogModel
        onModelReloaded: {
            renewColumns();
        }

        onTitlesChanged: {
            for (var i = 0; i < logViewer.columnCount; i++) {
                var column = logViewer.getColumn(i);
                column.title = LogModel.getTitle(column.role);
            }
        }
    }
}
