import QtQuick
import QtQuick.Controls

import qml.components
import "../components"

// MenuBar with: Options / Mode / Folders / Info
MenuBar {

    id: root
    property var mode
    property bool database

    signal dlgNewFolder
    signal dlgSettings
    signal dlgHistory
    signal undo
    signal redo
    signal folderImages
    signal folderFavorites
    signal folderTrash
    signal refreshUI
    signal changeMode(var newMode)
    signal changePath
    signal dlgInfo
    signal dlgPlugins
    signal openWebsite

    Menu {
        title: "Options"

        MenuDefault {
            text: "Change Path"
            icon.source: "qrc:/icons/flaticon/folder.png"
            onTriggered: root.changePath()
        }
        MenuDefault {
            text: "Settings"
            icon.source: "qrc:/icons/flaticon/settings.png"
            onTriggered: root.dlgSettings()
        }
        MenuDefault {
            text: "UnDo"
            icon.source: "qrc:/icons/flaticon/undo.png"
            onTriggered: root.undo()
        }
        MenuDefault {
            text: "ReDo"
            icon.source: "qrc:/icons/flaticon/redo.png"
            onTriggered: root.redo()
        }
        MenuDefault {
            text: "History"
            icon.source: "qrc:/icons/flaticon/history.png"
            onTriggered: root.dlgHistory()
        }
        MenuDefault {
            text: "Refresh"
            icon.source: "qrc:/icons/flaticon/refresh.png"
            onTriggered: root.refreshUI()
        }
    }

    Menu {
        id: modeMenu
        title: "Mode"

        MenuCheckBox {
            text: "Gallery"
            icon.source: "qrc:/icons/flaticon/gallery.png"
            mode: root.mode === Options.Gallery
            onClicked: {
                root.changeMode(Options.Gallery)
                modeMenu.dismiss() // Close menu
            }
        }
        MenuCheckBox {
            text: "Image"
            icon.source: "qrc:/icons/flaticon/image.png"
            mode: root.mode === Options.Image
            onClicked: {
                root.changeMode(Options.Image)
                modeMenu.dismiss() // Close menu
            }
        }
        MenuCheckBox {
            text: "Video"
            icon.source: "qrc:/icons/flaticon/video.png"
            mode: root.mode === Options.Video
            onClicked: {
                root.changeMode(Options.Video)
                modeMenu.dismiss() // Close menu
            }
        }
        MenuCheckBox {
            text: "Compare"
            icon.source: "qrc:/icons/flaticon/compare.png"
            mode: root.mode === Options.Compare
            onClicked: {
                root.changeMode(Options.Compare)
                modeMenu.dismiss() // Close menu
            }
        }
        MenuCheckBox {
            text: "Database"
            icon.source: "qrc:/icons/flaticon/database.png"
            mode: root.mode === Options.Database
            enabled: root.database
            onClicked: {
                root.changeMode(Options.Database)
                modeMenu.dismiss() // Close menu
            }
        }
    }

    Menu {
        title: "Folders"

        MenuDefault {
            text: "Add Folder"
            icon.source: "qrc:/icons/flaticon/folder_add.png"
            onTriggered: root.dlgNewFolder()
        }
        MenuDefault {
            text: "Current Path"
            icon.source: "qrc:/icons/flaticon/folder_image.png"
            onTriggered: root.folderImages()
        }
        MenuDefault {
            text: "Favorits"
            icon.source: "qrc:/icons/flaticon/folder_favorite.png"
            onTriggered: root.folderFavorites()
        }
        MenuDefault {
            text: "Trash"
            icon.source: "qrc:/icons/flaticon/folder_trash.png"
            onTriggered: root.folderTrash()
        }
    }

    Menu {
        title: "Info"

        MenuDefault {
            text: "Plugins"
            icon.source: "qrc:/icons/flaticon/plugin.png"
            onTriggered: root.dlgPlugins()
        }
        MenuDefault {
            text: "Website"
            icon.source: "qrc:/icons/flaticon/website.png"
            onTriggered: root.openWebsite()
        }
        MenuDefault {
            text: "About"
            icon.source: "qrc:/icons/flaticon/info.png"
            onTriggered: root.dlgInfo()
        }
    }
}
