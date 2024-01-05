import QtQuick
import QtQuick.Controls

// File item with image or video
Item {

    id: root
    property string type
    property string path
    property string duration
    property string frame
    property bool isActive
    property size sourceSize
    signal indexUp
    signal indexDown
    signal imageLoaded
    signal browse

    function seekUp() {
        if (type === "Video")
            video.item.seekUp()
    }

    function seekDown() {
        if (type === "Video")
            video.item.seekDown()
    }

    function pause() {
        if (type === "Video")
            video.item.pause()
    }

    function close() {
        if (type === "Video")
            video.item.close()
    }

    function rotateImage(direction) {
        if (type === "Image")
            image.item.setRotation(direction)
    }

    state: root.type
    states: [
        State {
            name: "Image"
            PropertyChanges {
                target: image
                active: true
            }
            PropertyChanges {
                target: video
                active: false
            }
        },
        State {
            name: "Video"
            PropertyChanges {
                target: image
                active: false
            }
            PropertyChanges {
                target: video
                active: true
            }
        }
    ]

    Loader {
        id: image
        anchors.fill: parent
        active: false
        sourceComponent: ImageItem {
            anchors.fill: parent
            source: root.path
            onClicked: root.browse()
            onIndexUp: root.indexUp()
            onIndexDown: root.indexDown()
            onImageLoaded: root.imageLoaded()
        }
    }
    Loader {
        id: video
        anchors.fill: parent
        active: false
        sourceComponent: VideoFrameItem {
            frame: root.frame
            source: root.path
            duration: root.duration
            sourceSize: root.sourceSize
            isActive: root.isActive
            onIndexUp: root.indexUp()
            onIndexDown: root.indexDown()
        }
    }
}
