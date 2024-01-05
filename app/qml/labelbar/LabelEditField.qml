import QtQuick
import QtQuick.Controls

import "../components"

// Label edit field
Item {

    id: root
    implicitWidth: addButton.width + editField.width

    property bool selected: false
    property int duration: 300
    signal addItem(string name)

    // Edit text field
    TextField {

        id: editField
        anchors.centerIn: parent
        width: 0
        height: parent.height

        // length and contentWidth are properties of TextField
        onLengthChanged: {
            if (contentWidth > 40)
                width = contentWidth + 20
            else
                width = 50
        }

        onAccepted: {
            root.addItem(text)
            root.state = "close"
        }

        selectByMouse: true
        placeholderText: "Label"
        placeholderTextColor: width > 0 ? "#60000000" : "transparent"
        color: width > 0 ? "black" : "transparent"
        maximumLength: 100
        leftPadding: 5
        rightPadding: 5
        topPadding: 0
        bottomPadding: 0

        background: Rectangle {
            color: "white"
            border.color: "black"
        }
    }

    // Button for open and close
    RoundButtonDefault {

        id: addButton
        objectName: "item unlock" // Needed for focus check
        anchors.verticalCenter: editField.verticalCenter
        anchors.leftMargin: 5
        anchors.left: editField.right
        text: "+"

        onClicked: {
            if (!root.selected)
                root.state = "open"
            else
                root.state = "close"
        }
    }

    state: "close"
    states: [
        State {
            name: "open"
            PropertyChanges {
                target: root
                selected: true
            }
            PropertyChanges {
                target: editField
                width: 50
                focus: true
                text: ""
            }
            PropertyChanges {
                target: addButton
                rotation: 45
                objectName: "item lock"
            }
        },
        State {
            name: "close"
            PropertyChanges {
                target: root
                selected: false
            }
            PropertyChanges {
                target: editField
                width: 0
                focus: false
                text: ""
            }
            PropertyChanges {
                target: addButton
                rotation: 0
                objectName: "item unlock"
            }
        }
    ]
    transitions: [
        Transition {
            ParallelAnimation {
                NumberAnimation {
                    target: editField
                    properties: "width"
                    duration: root.duration
                }
                RotationAnimation {
                    target: addButton
                    duration: root.duration
                }
            }
        }
    ]
}
