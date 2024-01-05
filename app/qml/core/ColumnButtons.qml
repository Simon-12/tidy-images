import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import qml.components
import "../components"

// Column with buttons on right side
Pane {

    id: root
    property bool favorite
    property bool isImage: mode === Options.Image || isFullscreen
    property bool isGallery: mode === Options.Gallery && !isFullscreen
    property bool isFullscreen
    property var mode
    property var model
    signal indexUp
    signal indexDown
    signal cmbOrder(int order)
    signal cmbDirection(int direction)
    signal btnFavorit
    signal btnCopy
    signal btnDelete
    signal btnRotate(bool direction)
    signal btnFolder(string path)
    signal btnClear
    signal btnAddFolder

    Material.elevation: 5
    Layout.fillHeight: true
    visible: mode === Options.Image || mode === Options.Video
             || mode === Options.Gallery

    ColumnLayout {
        anchors.fill: parent

        // Column with main buttons
        Column {
            spacing: 5

            Label {
                text: "Sort Order"
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
            }

            ComboBoxDefault {
                // Order
                model: ["Name", "Type", "Recorded", "Created", "Modified"]
                onCurrentIndexChanged: {
                    root.cmbOrder(currentIndex) // currentIndex is property
                    if (currentIndex <= 1)
                        boxOrder.model = ["A - Z", "Z - A"]
                    else
                        boxOrder.model = ["Old - New", "New - Old"]
                }
            }

            ComboBoxDefault {
                // Direction
                id: boxOrder
                model: ["A - Z", "Z - A"]
                onCurrentIndexChanged: root.cmbDirection(
                                           currentIndex) // currentIndex is property
            }

            Item {
                // Freespace
                width: 1
                height: 50
                visible: !root.isGallery
            }

            Row {
                spacing: 5
                visible: !root.isGallery

                ButtonDefault {
                    implicitWidth: 57.5
                    icon.source: "qrc:/icons/material/back.png"
                    onClicked: root.indexDown()
                }

                ButtonDefault {
                    implicitWidth: 57.5
                    icon.source: "qrc:/icons/material/next.png"
                    onClicked: root.indexUp()
                }
            }

            Row {
                spacing: 5
                visible: root.isImage

                ButtonDefault {
                    implicitWidth: 57.5
                    topPadding: 2 // Adjustt icon
                    iconSize: 28
                    icon.source: "qrc:/icons/material/rotate_left.png"
                    onClicked: root.btnRotate(false)
                }

                ButtonDefault {
                    implicitWidth: 57.5
                    topPadding: 2 // Adjustt icon
                    iconSize: 28
                    icon.source: "qrc:/icons/material/rotate_right.png"
                    onClicked: root.btnRotate(true)
                }
            }

            Item {
                // Freespace
                width: 1
                height: 50
            }

            ButtonDefault {
                text: "Clear"
                iconSize: 21
                icon.source: "qrc:/icons/material/square.svg"
                visible: root.isGallery
                onClicked: root.btnClear()
            }

            ButtonDefault {
                text: "Favorit"
                icon.source: root.favorite
                             || root.isGallery ? "qrc:/icons/flaticon/star_1.png" : "qrc:/icons/flaticon/star_2.png"
                onClicked: root.btnFavorit()
            }

            ButtonDefault {
                text: "Copy"
                icon.source: "qrc:/icons/flaticon/copy.png"
                onClicked: root.btnCopy()
            }

            ButtonDefault {
                text: "Delete"
                icon.source: "qrc:/icons/flaticon/trash.png"
                onClicked: root.btnDelete()
            }

            Item {
                // Freespace
                width: 1
                height: 50
            }
        }

        ListButtons {
            // Dynamic buttons
            Layout.preferredWidth: parent.width
            Layout.fillHeight: true
            model: root.model
            onClick: path => root.btnFolder(path)
            onAddFolder: root.btnAddFolder()
        }
    }
}
