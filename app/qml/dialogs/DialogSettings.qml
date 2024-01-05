import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import qml.components
import "."  // For debug project (needs to be in this line)
import "../components"

// Popup with application settings
PopupDefault {
    id: root
    property string path
    property string folders
    property string database
    property string favorites
    property string trash
    property bool databaseActive
    signal changePath(string path, var option)
    signal changeDatabase(bool option)
    signal addDatabase
    signal removeDatabase

    Column {
        // Main layout
        anchors.fill: parent
        spacing: 10

        Pane {

            Material.elevation: 5
            Column {
                spacing: 10

                Label {
                    text: "Application Paths"
                    width: parent.width
                    font.bold: true
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                }
                PathBox {
                    name: "Path"
                    icon: "qrc:/icons/flaticon/folder.png"
                    path: root.path
                    onBrowse: root.changePath(path, Options.CurrentPath)
                }
                PathBox {
                    name: "Folders"
                    icon: "qrc:/icons/flaticon/folder_add.png"
                    path: root.folders
                    onBrowse: root.changePath(path, Options.FolderFile)
                }
                PathBox {
                    name: "Database"
                    icon: "qrc:/icons/flaticon/database.png"
                    path: root.database
                    onBrowse: root.changePath(path, Options.DatabaseFile)
                }
                PathBox {
                    name: "Favorites"
                    icon: "qrc:/icons/flaticon/folder_favorite.png"
                    path: root.favorites
                    onBrowse: root.changePath(path, Options.FavoritesFolder)
                }
                PathBox {
                    name: "Trash"
                    icon: "qrc:/icons/flaticon/folder_trash.png"
                    path: root.trash
                    onBrowse: root.changePath(path, Options.TrashFolder)
                }
            }
        }

        Pane {

            Material.elevation: 5
            Column {
                spacing: 12

                RowLayout {
                    width: parent.width

                    Label {
                        text: "Database"
                        Layout.fillWidth: true
                        font.bold: true
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                    }
                    Label {
                        text: "Enabled"
                        font.pointSize: 12
                    }
                    CheckBox {
                        checked: root.databaseActive
                        padding: 0
                        verticalPadding: 0
                        onClicked: root.changeDatabase(checked)
                    }
                }

                RowLayout {
                    width: parent.width
                    spacing: 10

                    Label {
                        text: "Current Path:"
                        bottomPadding: 10
                        font.pointSize: 12
                        font.bold: true
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                    }
                    TextField {
                        Layout.fillWidth: true
                        topPadding: 0
                        bottomPadding: 10
                        text: root.path
                        font.pointSize: 10
                        selectByMouse: true
                    }
                }

                Row {
                    spacing: 10

                    ButtonDefault {
                        implicitWidth: 220
                        text: "Add Path"
                        iconSize: 20
                        icon.source: "qrc:/icons/flaticon/database_add.png"
                        onClicked: root.addDatabase()
                        enabled: root.databaseActive
                    }
                    ButtonDefault {
                        implicitWidth: 220
                        text: "Remove Path"
                        iconSize: 20
                        icon.source: "qrc:/icons/flaticon/database_remove.png"
                        onClicked: root.removeDatabase()
                        enabled: root.databaseActive
                    }
                }
            }
        }
    }
}
