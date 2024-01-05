import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import qml.components

// Bottom status bar
Item {

    id: root
    property var mode
    property bool isFullscreen
    property list<string> status

    height: 25
    visible: mode === Options.Image || mode === Options.Video || isFullscreen
    onVisibleChanged: state = visible ? "true" : "false"

    ToolBar {

        anchors.fill: parent
        Material.elevation: 15

        Item {
            anchors.fill: parent

            // Name
            Label {
                text: root.status[0] ? root.status[0] : ""
                font.family: "Roboto Mono"
                font.pointSize: 12
                anchors.left: parent.left
                anchors.leftMargin: 10
            }

            // Date
            Label {
                id: labelCenter
                text: root.status[1] ? root.status[1] : ""
                font.family: "Roboto Mono"
                font.pointSize: 12
                anchors.centerIn: parent
            }

            // Type
            Label {
                text: root.status[2] ? root.status[2] : ""
                font.family: "Roboto Mono"
                font.pointSize: 12
                anchors.left: labelCenter.right
                anchors.leftMargin: 100
            }

            // Number
            Label {
                text: root.status[3] ? root.status[3] : ""
                font.family: "Roboto Mono"
                font.pointSize: 12
                anchors.right: parent.right
                anchors.rightMargin: 10
            }
        }
    }

    states: [
        State {
            name: "true"
            PropertyChanges {
                target: root
                height: 25
            }
            PropertyChanges {
                target: root
                opacity: 1
            }
        },
        State {

            name: "false"
            PropertyChanges {
                target: root
                height: 0
            }
            PropertyChanges {
                target: root
                opacity: 0
            }
        }
    ]
    transitions: [
        Transition {
            from: "false"
            to: "true"
            NumberAnimation {
                target: root
                properties: "height"
                duration: 500
            }
            OpacityAnimator {
                target: root
                duration: 500
            }
        }
    ]
}
