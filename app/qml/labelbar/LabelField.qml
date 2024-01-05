import QtQuick
import QtQuick.Controls

import "../components"

// Label item with text
Item {

    id: root
    implicitWidth: label.width + removeButton.width + offset

    property int offset: 22
    property string text
    property int duration: 300
    signal clicked

    // Label background
    Rectangle {
        id: box
        anchors.fill: parent
        color: "#e0e0e0" // light gray
        radius: height / 2
    }

    // Text label
    Label {
        id: label
        text: root.text
        font.pointSize: 12
        anchors.centerIn: box
        anchors.horizontalCenterOffset: -10
    }

    // Remove Button
    RoundButtonDefault {
        id: removeButton
        text: "-"
        anchors.left: label.right
        anchors.leftMargin: 12
        anchors.verticalCenter: box.verticalCenter

        onClicked: {
            label.color = "transparent"
            root.state = "close"
            root.clicked()
        }
    }

    state: "open"
    states: [
        State {
            name: "open"
        },
        State {
            name: "close"
            PropertyChanges {
                target: label
                width: 0
            }
            PropertyChanges {
                target: removeButton
                width: 0
            }
            PropertyChanges {
                target: box
                opacity: 0
            }
            PropertyChanges {
                target: root
                offset: 0
            }
        }
    ]
    transitions: [
        Transition {
            from: "open"
            to: "close"
            SequentialAnimation {
                PropertyAction {
                    target: root
                    property: "ListView.delayRemove"
                    value: true
                }
                PropertyAnimation {
                    target: label
                    property: "width"
                    duration: root.duration / 2
                }
                PropertyAnimation {
                    target: removeButton
                    property: "width"
                    duration: root.duration / 2
                }
                OpacityAnimator {
                    target: box
                    duration: root.duration
                }
                PropertyAnimation {
                    target: root
                    property: "offset"
                    duration: root.duration / 2
                }
                PropertyAction {
                    target: root
                    property: "ListView.delayRemove"
                    value: false
                }
            }
        }
    ]
}
