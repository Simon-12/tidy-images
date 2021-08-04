import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.12

import qml.options 1.0


// Bottom status bar
Item {

    id: root    
    property var mode
    property bool isFullscreen
    property string status

    height: 25
    visible: mode === Options.Image || mode === Options.Video || isFullscreen
    onVisibleChanged: state = visible ? "true" : "false"

    ToolBar {

        anchors.fill: parent
        Material.elevation: 15

        RowLayout {
            anchors.fill: parent

            Label {
                text: root.status
                font.family: "Roboto Mono"
                font.pointSize: 11
                Layout.leftMargin: 10
                Layout.rightMargin: 10
            }
        }
    }

    states: [
        State {
            name: "true"
            PropertyChanges { target: root; height: 25}
            PropertyChanges { target: root; opacity: 1}
        },
        State {

            name: "false"
            PropertyChanges { target: root; height: 0}
            PropertyChanges { target: root; opacity: 0}
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
