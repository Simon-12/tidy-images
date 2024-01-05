import QtQuick
import QtQuick.Controls

// SwipeView with images
Item {

    id: root
    anchors.fill: parent
    property var model
    property int index
    property int bufferSize
    signal newIndex(int index)
    signal indexUp
    signal indexDown
    signal imageLoaded(int image)

    // Avoid binding loop
    Component.onCompleted: swipeView.setCurrentIndex(0)
    onIndexChanged: swipeView.setCurrentIndex(index)

    // Default handling
    onIndexUp: swipeView.incrementCurrentIndex()
    onIndexDown: swipeView.decrementCurrentIndex()

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

                active: Math.abs(
                            swipeView.currentIndex - index) < root.bufferSize
                        && model.name !== undefined
                sourceComponent: ImageItem {
                    source: model.name
                    onClicked: root.model.browse(index)
                    onIndexUp: root.indexUp()
                    onIndexDown: root.indexDown()
                    onImageLoaded: root.imageLoaded(index)
                }
            }
        }
    }

    function rotateImage(direction) {
        // Access the current item: Repeater -> Loader -> Image
        container.itemAt(swipeView.currentIndex).item.setRotation(direction)
    }
}
