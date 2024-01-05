import QtQuick
import QtQuick.Controls

import qml.components
import "../components"

// Database header buttons
Item {

    id: root
    property string name
    property var direction
    signal clicked

    onDirectionChanged: {
        switch (direction) {
        case Options.Disabled:
            icon.source = ""
            break
        case Options.Low:
            icon.source = "qrc:/icons/material/arrow_down.png"
            break
        case Options.High:
            icon.source = "qrc:/icons/material/arrow_up.png"
            break
        default:
            break
        }
    }

    Button {

        id: control
        anchors.fill: parent
        text: root.name
        onClicked: root.clicked()

        font.capitalization: Font.MixedCase
        hoverEnabled: true

        contentItem: Item {
            anchors.fill: parent
            anchors.margins: 5

            Label {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                text: control.text
                font: control.font
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            ImageDefault {
                id: icon
                width: 26
                height: 26
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        background: BackgroundDefault {}
    }
}
