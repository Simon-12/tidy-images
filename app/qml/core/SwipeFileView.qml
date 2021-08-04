import QtQuick 2.15
import QtQuick.Controls 2.15

import "../core"


// SwipeView with images and videos
Item {

    id: root
    property var model
    property int index
    property int bufferSize
    signal indexUp()
    signal indexDown()
    signal newIndex(var index)
    signal imageLoaded(var image)

    // Avoid binding loop
    Component.onCompleted: swipeView.setCurrentIndex(0)
    onIndexChanged: swipeView.setCurrentIndex(index)

    // Default handling
    onIndexUp: swipeView.incrementCurrentIndex()
    onIndexDown: swipeView.decrementCurrentIndex()

    function seekUp() {
        // Access the current item: Repeater -> Loader[0] -> Item
        container.itemAt(swipeView.currentIndex).children[0].seekUp()
    }

    function seekDown() {
        container.itemAt(swipeView.currentIndex).children[0].seekDown()
    }

    function pause() {
        container.itemAt(swipeView.currentIndex).children[0].pause()
    }

    function rotateImage(direction) {
        container.itemAt(swipeView.currentIndex).children[0].rotateImage(direction)
    }

    SwipeView {

        id: swipeView
        anchors.fill: parent
        interactive: false
        clip: true
        onCurrentIndexChanged: root.newIndex(currentIndex)

        Repeater {
            id: container
            model: root.model

            delegate: Loader {
                id: loader
                property bool isCurrentItem: SwipeView.isCurrentItem
                active: Math.abs(swipeView.currentIndex - index) < root.bufferSize && model.type !== undefined
                sourceComponent: FileItem {
                    type: model.type
                    path: model.path
                    duration: model.duration
                    frame: model.frame
                    sourceSize: Qt.size(width, height)
                    isActive: loader.isCurrentItem
                    onIndexUp: root.indexUp()
                    onIndexDown: root.indexDown()
                    onImageLoaded: root.imageLoaded(index)
                    onBrowse: root.model.browse(index)
                }
            }
        }
    }
}
