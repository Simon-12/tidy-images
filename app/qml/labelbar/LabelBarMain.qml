import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.12

import qml.options 1.0


// Label bar on top side
Item {

    id: root
    property var mode
    property var model
    property bool isFullscreen
    signal addLabel(var string)
    signal removeLabel(var num)

    height: 30
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
                    onAddItem: root.addLabel(string)
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
            PropertyChanges { target: root; height: 30; opacity: 1 }
        },
        State {
            name: "false"
            PropertyChanges { target: root; height: 0; opacity: 0 }
        }
    ]
    transitions: [
        Transition {
            from: "false"; to: "true"
            NumberAnimation { target: root; properties: "height"; duration: 500 }
            OpacityAnimator { target: root; duration: 500 }
        }
    ]
}

