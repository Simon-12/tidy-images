import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import qml.options 1.0
import "../components"


// Database header buttons
Item {

    id: root
    property string name
    property var direction
    signal clicked()

    onDirectionChanged: {
        switch(direction)
        {
        case Options.Disabled: icon.source = ""; break
        case Options.Low:      icon.source = "qrc:/icons/material/arrow_down.png"; break
        case Options.High:     icon.source = "qrc:/icons/material/arrow_up.png"; break
        default: break
        }
    }

    Button {

        id: control
        anchors.fill: parent
        text: root.name
        onClicked: root.clicked()

        font.capitalization: Font.MixedCase
        hoverEnabled: true

        contentItem: RowLayout {

            anchors.fill: parent
            anchors.margins: 5

            Label {
                Layout.fillWidth: true
                Layout.fillHeight: true

                text: control.text
                font: control.font
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            ImageDefault {
                id: icon
                Layout.preferredWidth: 26
                Layout.preferredHeight: 26
            }
        }

        background: BackgroundDefault { }
    }
}
