import QtQuick 2.15
import QtQuick.Controls 2.15

import "../components"


// Video frame as image and playable video
Item {

    id: root
    state: "frame"
    property string frame
    property string source
    property string duration
    property bool isActive
    property alias sourceSize: videoFrame.sourceSize
    signal indexUp()
    signal indexDown()

    function seekUp() {
        if(videoView.active) videoView.item.seekUp()
    }

    function seekDown() {
        if(videoView.active) videoView.item.seekDown()
    }

    function pause() {
        if(videoView.active) videoView.item.pause()
    }

    onIsActiveChanged: {
        state = "frame"
    }

    ImageItem {
        id: videoFrame
        anchors.centerIn: parent
        width: sourceSize.width
        height: sourceSize.height

        source: "image://videoFrame/" + root.frame
        fillMode: Image.Pad
        onIndexUp: root.indexUp()
        onIndexDown: root.indexDown()

        // Play button
        Triangle {
            anchors.centerIn: parent
            visible: root.width > 50
            onClicked: root.state = "video"
        }

        // Duration
        Rectangle {
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            visible: root.width > 50 && root.duration != ""
            width: label.width + 10
            height: 20
            radius: height / 2
            opacity: 0.7
            color: "gray"

            Label {
                id: label
                anchors.centerIn: parent
                color: "white"
                text: root.duration
            }
        }
    }

    Loader {
        id: videoView
        width: parent.width
        height: parent.height
        x: 0
        y: parent.height

        active: false
        sourceComponent: VideoItem {
            source: root.source
            onCloseVideo: root.state = "frame"
        }
    }

    // States and animation
    states: [
        State { name: "frame" },
        State { name: "video" }
    ]
    transitions: [
        Transition {
            from: "frame"; to: "video"
            SequentialAnimation {
                PropertyAction { target: videoView; property: "active"; value: true } // Activate video element
                ParallelAnimation {
                    OpacityAnimator { target: videoFrame; from: 1; to: 0; duration: 350 }
                    PropertyAnimation { target: videoView; property: "y"; from: root.height; to: 0; duration: 500 }
                }
                ScriptAction { script: { videoView.item.pause(); videoView.item.showClose = true } } // Start video directly and show button
            }
        },
        Transition {
            from: "video"; to: "frame"
            SequentialAnimation {
                ScriptAction { script: { videoView.item.stop(); videoView.item.showClose = false } } // Stop video and hide button
                ParallelAnimation {
                    OpacityAnimator { target: videoFrame; from: 0; to: 1; duration: 350 }
                    PropertyAnimation { target: videoView; property: "y"; from: 0; to: root.height; duration: 500 }
                }
                PropertyAction { target: videoView; property: "active"; value: false } // Deactivate video element
            }
        }
    ]
}
