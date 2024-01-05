import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import qml.components

// Label bar on top side
Item {

    id: root
    property var mode
    property var model
    property bool isFullscreen
    signal addLabel(string name)
    signal removeLabel(int num)

    height: 35
    visible: mode === Options.Image || mode === Options.Video || isFullscreen
    onVisibleChanged: state = visible ? "true" : "false"

    ToolBar {
        anchors.fill: parent
        Material.elevation: 1

        Rectangle {
            anchors.fill: parent
            color: "transparent"
            border.color: "black"
            border.width: 1

            RowLayout {
                anchors.fill: parent

                Label {
                    text: "Labels:"
                    Layout.leftMargin: 10
                    Layout.rightMargin: -10
                }

                LabelEditField {
                    Layout.preferredHeight: parent.height - 10
                    Layout.rightMargin: 30
                    onAddItem: name => root.addLabel(name)
                }

                ListView {
                    id: view
                    orientation: ListView.Horizontal
                    spacing: 20
                    Layout.fillWidth: true
                    Layout.preferredHeight: parent.height - 10

                    model: root.model

                    delegate: LabelField {
                        id: label
                        text: model.name
                        height: view.height
                        onClicked: root.removeLabel(index) // index is property
                    }
                }
            }
        }
    }

    states: [
        State {
            name: "true"
            PropertyChanges {
                target: root
                height: 35
                opacity: 1
            }
        },
        State {
            name: "false"
            PropertyChanges {
                target: root
                height: 0
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
