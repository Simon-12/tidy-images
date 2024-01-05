import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "../components"

// Delegate for history dialog
Item {

    id: root
    property string name
    property string folder
    property string source
    property int number
    property bool empty
    property bool selected
    signal clicked

    Pane {
        anchors.fill: parent
        padding: 0
        bottomPadding: -1
        Material.elevation: 5

        // Item background
        Rectangle {
            anchors.fill: parent
            property color cDefault: "transparent"
            property color cHovered: "#e0e0e0" // light gray
            property color cpressed: "gray"
            property color cSelected: "#9FA8DA" // indigo (shade)
            color: area.pressed ? cpressed : area.hovered ? cHovered : root.selected ? cSelected : cDefault
        }

        RowLayout {
            anchors.fill: parent
            anchors.margins: 5
            spacing: 15

            // Background
            Rectangle {
                visible: !root.empty
                color: "black"
                implicitWidth: 40
                implicitHeight: 35

                ImageDefault {
                    anchors.fill: parent
                    anchors.margins: 1
                    source: visible ? root.source : ""
                }
            }

            Label {
                text: root.name
                font.italic: root.empty
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true

                horizontalAlignment: root.empty ? Text.AlignHCenter : Text.AlignLeft
                verticalAlignment: root.number > 2 ? Text.AlignTop : Text.AlignVCenter
            }

            ImageDefault {
                Layout.preferredWidth: 40
                Layout.preferredHeight: 35
                source: "qrc:/icons/material/arrow_right.png"
            }

            Label {
                text: root.folder
                font.bold: true
                font.italic: root.empty
                Layout.preferredWidth: 150
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        MouseArea {
            id: area
            anchors.fill: parent
            hoverEnabled: true
            property bool hovered: false
            onEntered: hovered = true
            onExited: hovered = false
            onClicked: root.clicked()
        }
    }
}
