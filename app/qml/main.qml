import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

import qml.components
import "dialogs"
import "labelbar"
import "compare"
import "database"
import "core"

ApplicationWindow {

    id: root
    title: "Tidy Images"
    visible: true
    width: controller.window.width
    height: controller.window.height

    Component.onCompleted: {
        // Center window on startup
        root.x = (Screen.desktopAvailableWidth / 2) - (width / 2)
        root.y = (Screen.desktopAvailableHeight / 2) - (height / 2)
        controller.startLoadFiles(false)
    }

    menuBar: MenuBarMain {
        mode: controller.mode
        database: controller.databaseActive
        onDlgNewFolder: dlgFolder.open()
        onDlgSettings: dlgSettings.open()
        onDlgHistory: dlgHistory.open()
        onUndo: controller.undo()
        onRedo: controller.redo()
        onFolderImages: controller.openExplorer(Options.Path)
        onFolderFavorites: controller.openExplorer(Options.Favorites)
        onFolderTrash: controller.openExplorer(Options.Trash)
        onRefreshUI: controller.updateController()
        onChangeMode: newMode => controller.changeMode(newMode)
        onChangePath: controller.changeCurrentPath()
        onDlgPlugins: dlgPlugin.open()
        onDlgInfo: dlgInfo.open()
        onOpenWebsite: dlgInfo.openWebsite()
    }

    header: LabelBarMain {
        id: labelBar
        mode: controller.mode
        isFullscreen: controller.fullscreen
        model: controller.listModels.labels
        onAddLabel: name => controller.addLabel(name)
        onRemoveLabel: num => controller.removeLabel(num)
    }

    footer: StatusBarMain {
        mode: controller.mode
        isFullscreen: controller.fullscreen
        status: controller.status
    }

    RowLayout {
        // Main layout
        anchors.fill: parent

        StackLayout {

            currentIndex: controller.mode

            // fillWidth + fillHeight is on true by default
            Loader {
                id: galleryView
                active: controller.mode === Options.Gallery
                sourceComponent: GalleryMain {
                    bufferSize: controller.loader.bufferSize
                    model: controller.listModels.files
                    view.index: controller.index
                    view.onIndexUp: controller.index++
                    view.onIndexDown: controller.index--
                    onGridIndexChanged: controller.index = gridIndex
                    onIsFullscreenChanged: controller.fullscreen = isFullscreen
                }
            }

            Loader {
                id: imageView
                active: controller.mode === Options.Image
                sourceComponent: SwipeImageView {
                    model: controller.listModels.images
                    index: controller.index
                    bufferSize: controller.loader.bufferSize
                    onIndexUp: controller.index++
                    onIndexDown: controller.index--
                    onImageLoaded: image => controller.loader.loadImage(image)
                }
            }

            Loader {
                id: videoView
                active: controller.mode === Options.Video
                sourceComponent: VideoItem {
                    source: controller.file
                }
            }

            Loader {
                active: controller.mode === Options.Compare
                sourceComponent: CompareMain {
                    images: controller.listModels.images
                    table: controller.listModels.table
                    progress: controller.loader.step
                    bufferSize: controller.loader.bufferSize
                    onImageLoaded: image => controller.loader.loadImage(image)
                    onBtnDelete: index => controller.deleteFile(index)
                    onStopCompare: controller.stopCompare()
                    onStartCompare: function (index) {
                        controller.loader.step = 0
                        controller.startCompare(index)
                    }
                }
            }

            Loader {
                id: database
                active: controller.mode === Options.Database
                sourceComponent: DatabaseMain {
                    headerModel: controller.listModels.header
                    databaseModel: controller.listModels.database
                    fileModel: controller.listModels.files
                    bufferSize: controller.loader.bufferSize
                }
            }

            Loader {
                active: controller.mode === Options.Empty
                sourceComponent: EmptyMain {
                    onChangePath: controller.changeCurrentPath()
                }
            }
        }

        ColumnButtons {
            // Main buttons
            favorite: controller.favorite
            isFullscreen: controller.fullscreen
            mode: controller.mode
            model: controller.selected
            onIndexUp: controller.index++
            onIndexDown: controller.index--
            onBtnFolder: function (path) {
                if (controller.mode === Options.Gallery)
                    galleryView.item.view.close()
                controller.moveFile(path)
            }
            onBtnFavorit: controller.fileFavorit()
            onBtnCopy: controller.copyFile()
            onBtnDelete: {
                if (controller.mode === Options.Gallery)
                    galleryView.item.view.close()
                controller.deleteFile()
            }
            onBtnClear: controller.listModels.files.clearSelected()
            onCmbOrder: order => controller.changeOrder(order)
            onCmbDirection: direction => controller.changeDirection(direction)
            onBtnAddFolder: dlgFolder.open()
            onBtnRotate: function (direction) {
                if (controller.mode === Options.Image)
                    imageView.item.rotateImage(direction)
                if (controller.mode === Options.Gallery)
                    galleryView.item.view.rotateImage(direction)
                controller.setRotation(direction)
            }
        }
    }

    // Dialogs
    DialogLoader {
        show: controller.loader.open
        size: controller.loader.size
        progress: controller.loader.progress
        text: controller.loader.text
    }

    DialogFolder {
        id: dlgFolder
        model: controller.folders
        onAddFoler: controller.addFolder()
    }

    DialogSettings {
        id: dlgSettings
        path: controller.paths.path
        folders: controller.paths.folders
        database: controller.paths.database
        favorites: controller.paths.favorites
        trash: controller.paths.trash
        databaseActive: controller.databaseActive
        onChangePath: (path, option) => controller.changePath(path, option)
        onAddDatabase: controller.addToDatabase()
        onRemoveDatabase: controller.removeFromDatabase()
        onChangeDatabase: option => controller.databaseActive = option
    }

    DialogHistory {
        id: dlgHistory
        model: controller.listModels.command
    }

    DialogPlugin {
        id: dlgPlugin
        model: controller.plugins
    }

    DialogInfo {
        id: dlgInfo
    }

    // Focus handling
    FocusHandler {
        id: focusHandler
        Keys.onRightPressed: {
            switch (controller.mode) {
            case Options.Image:
                controller.index++
                break
            case Options.Video:
                videoView.item.seekUp()
                break
            case Options.Gallery:
                galleryView.item.view.seekUp()
                break
            case Options.Database:
                database.item.view.seekUp()
                break
            default:
                break
            }
        }
        Keys.onLeftPressed: {
            switch (controller.mode) {
            case Options.Image:
                controller.index--
                break
            case Options.Video:
                videoView.item.seekDown()
                break
            case Options.Gallery:
                galleryView.item.view.seekDown()
                break
            case Options.Database:
                database.item.view.seekDown()
                break
            default:
                break
            }
        }
        Keys.onUpPressed: {
            if (controller.mode === Options.Database)
                database.item.view.indexDown()
        }
        Keys.onDownPressed: {
            if (controller.mode === Options.Database)
                database.item.view.indexUp()
        }
        Keys.onSpacePressed: {
            switch (controller.mode) {
            case Options.Video:
                videoView.item.pause()
                break
            case Options.Gallery:
                galleryView.item.view.pause()
                break
            case Options.Database:
                database.item.view.pause()
                break
            default:
                break
            }
        }

        // Selects multiple items on STRG pressed
        Keys.onPressed: function (event) {
            if (controller.mode !== Options.Gallery)
                return
            if (event.key === Qt.Key_Control)
                controller.listModels.files.setMultiple(true)
        }
        Keys.onReleased: function (event) {
            if (controller.mode !== Options.Gallery)
                return
            if (event.key === Qt.Key_Control)
                controller.listModels.files.setMultiple(false)
        }
    }
    onFocusObjectChanged: focusHandler.checkFocus(activeFocusItem)
}
