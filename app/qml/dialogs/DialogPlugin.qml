import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "../components"

// Popup with infos about the installed plugins
PopupDefault {

    id: root
    property var model

    Column {
        anchors.fill: parent
        spacing: 10

        Label {
            text: "Plugins"
            font.bold: true
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        ListView {
            id: view
            width: 500
            height: 200
            spacing: 7
            model: root.model
            delegate: Pane {
                width: view.width
                height: 55
                padding: 0
                Material.elevation: 5

                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                    spacing: 15
                    ImageDefault {
                        Layout.preferredWidth: 41
                        Layout.preferredHeight: 41
                        source: model.icon
                    }
                    Column {
                        Layout.preferredWidth: 120
                        spacing: 5

                        Label {
                            text: model.name
                            font.pointSize: 12
                            font.bold: true
                        }
                        Label {
                            text: model.version
                            font.pointSize: 10
                        }
                    }
                    LabelLink {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        text: model.description
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }
    }
}
