import QtQuick 2.15
import QtQuick.Controls 2.15


// Database table
Item {

    id: root
    property var model
    property var widthArray
    property int index: 0
    signal clicked(var row)

    TableView {

        anchors.fill: parent
        columnSpacing: 10
        rowSpacing: 0
        interactive: false

        ScrollBar.vertical: ScrollBar {
            id: scrollbar
            width: 7
        }

        model: root.model

        delegate: Rectangle {

            implicitWidth: root.widthArray[column]
            implicitHeight: 20
            visible: width > 10 // Hide last column
            color: model.row === root.index ? "#B0BEC5" : "white" // Material.BlueGrey (shade)

            // Background border
            Rectangle {
                z : -1
                color: "black"
                anchors.fill: parent
                anchors.topMargin: -1
                anchors.leftMargin: -1
                anchors.rightMargin: -1
                anchors.bottomMargin: -1
            }

            Text {
                text: model.display
                anchors.fill: parent
                anchors.leftMargin: 5
                clip: true
                font.family: "Roboto Mono"
                font.pointSize: 10
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: root.clicked(row)
                onWheel: {
                    if(wheel.angleDelta.y > 0) scrollbar.decrease()
                    if(wheel.angleDelta.y < 0) scrollbar.increase()
                }
            }
        }
    }
}
