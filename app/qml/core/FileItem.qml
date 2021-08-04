import QtQuick 2.15
import QtQuick.Controls 2.15


// File item with image or video
Item {

    id: root
    property string type
    property string path
    property string duration
    property string frame
    property bool isActive
    property size sourceSize
    signal indexUp()
    signal indexDown()
    signal imageLoaded()
    signal browse()

    function seekUp() {
        if(state === "Video")
            video.item.seekUp()
    }

    function seekDown() {
        if(state === "Video")
            video.item.seekDown()
    }

    function pause() {
        if(state === "Video")
            video.item.pause()
    }

    function rotateImage(direction) {
        if(state === "Image")
            image.item.setRotation(direction)
    }

    state: root.type
    states: [
        State { name: "Image"
            PropertyChanges { target: image; active: true }
            PropertyChanges { target: video; active: false }
        },
        State { name: "Video"
            PropertyChanges { target: image; active: false }
            PropertyChanges { target: video; active: true }
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
