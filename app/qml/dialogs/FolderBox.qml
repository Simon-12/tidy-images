import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "../components"

// Delegate for folder dialog
Item {

    id: root

    property string name
    property string path
    property bool checked
    signal clicked
    signal browse
    signal remove

    Pane {
        anchors.fill: parent
        Material.elevation: 5
        leftPadding: 10
        rightPadding: 10
        padding: 0

        RowLayout {
            anchors.fill: parent
            spacing: 15

            CheckBox {
                padding: 0
                verticalPadding: 0
                checked: root.checked
                onClicked: root.clicked()
            }

            Label {
                text: root.name
                font.pointSize: 12
                font.bold: true
                Layout.preferredWidth: 140
            }

            TextField {
                Layout.fillWidth: true
                topPadding: 0
                bottomPadding: 0
                text: root.path
                font.pointSize: 10
                onAccepted: root.browse()
                onEditingFinished: text = root.path
                selectByMouse: true
            }

            ButtonIcon {
                onClicked: root.browse()
                icon.source: "qrc:/icons/flaticon/folder_search.png"
            }

            ButtonIcon {
                onClicked: root.remove()
                iconSize: 18
                icon.source: "qrc:/icons/flaticon/remove.png"
            }
        }
    }
}
