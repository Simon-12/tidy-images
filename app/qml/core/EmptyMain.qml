import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "../components"

// Empty view item
Item {

    id: root
    anchors.fill: parent
    signal changePath

    ColumnLayout {

        anchors.centerIn: parent
        spacing: 30

        Label {
            text: "Current path is empty!"
            font.pointSize: 18
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        Image {
            Layout.alignment: Qt.AlignHCenter
            source: "qrc:/icons/flaticon/empty.png"
            fillMode: Image.Pad
        }

        ButtonDefault {
            text: "Change Path"
            iconSize: 24
            implicitWidth: 220
            Layout.alignment: Qt.AlignHCenter
            icon.source: "qrc:/icons/flaticon/folder.png"
            onClicked: root.changePath()
        }
    }
}
