import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "../components"

// Popup to add new or activate folders
PopupDefault {
    id: root
    property var model
    signal addFoler

    ColumnLayout {
        // Main layout
        id: container
        anchors.fill: parent
        spacing: 15

        RowLayout {
            Label {
                text: "Select Folders"
                font.bold: true
                width: 100
                height: 35
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
            }

            Item {
                // Freespace
                Layout.fillWidth: true
                height: 1
            }

            ButtonDefault {
                implicitWidth: 150
                font.bold: true
                iconSize: 20
                icon.source: "qrc:/icons/flaticon/add.png"
                onClicked: root.addFoler()
            }
        }

        Column {
            Layout.preferredWidth: 600
            Layout.preferredHeight: 600
            spacing: 15

            Repeater {
                model: root.model
                delegate: FolderBox {
                    width: parent.width
                    height: 50
                    name: model.name
                    checked: model.selected
                    path: model.path
                    onRemove: root.model.remove(index)
                    onBrowse: root.model.browse(index)
                    onClicked: model.selected = !checked
                }
            }
        }
    }
}
