import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts
import QtMultimedia

import "SupportFunctions.js" as SF
import "../components"

// Video item with undock option
Item {

    id: root
    anchors.fill: parent
    property string source
    property bool showClose: false
    signal closeVideo

    function seekUp() {
        video.seek(video.position + 15000)
    }

    function seekDown() {
        video.seek(video.position - 15000)
    }

    function pause() {
        video.playback()
    }

    function stop() {
        video.pause()
    }

    Item {
        id: container
        anchors.fill: parent

        ColumnLayout {
            anchors.fill: parent

            ButtonClose {
                id: btnClose
                Layout.alignment: Qt.AlignRight
                onClicked: root.closeVideo()
            }

            Video {
                id: video
                Layout.fillWidth: true
                Layout.fillHeight: true

                source: root.source
                volume: btnsVideo.volume
                fillMode: VideoOutput.PreserveAspectFit // Fit without cropping

                // Useful properties:
                // position - current video position (ms)
                // duration - video duration (ms)
                // bufferProgress - 0.0 (empty) to 1.0 (full)
                // notifyInterval: 100 // interval at which notifiable position will update.
                // Missing in Qt6
                // flushMode: VideoOutput.EmptyFrame // When playback is finished or stopped
                onPositionChanged: btnsVideo.label = SF.msToString(
                                       position) + " | " + SF.msToString(
                                       duration)
                onPlaybackStateChanged: {
                    switch (playbackState) {
                    case MediaPlayer.PlayingState:
                        console.log("Video playback state:", "playing")
                        break
                    case MediaPlayer.PausedState:
                        console.log("Video playback state:", "paused")
                        break
                    case MediaPlayer.StoppedState:
                        console.log("Video playback state:", "stopped")
                        break
                    }
                    if (playbackState == MediaPlayer.PlayingState)
                        btnsVideo.play = false
                    else
                        btnsVideo.play = true
                }

                // Missing in Qt6

                /*
                onStatusChanged: {
                    switch (status)
                    {
                    case MediaPlayer.NoMedia:       console.log("Video status:", "NoMedia"); break
                    case MediaPlayer.Loading:       console.log("Video status:", "Loading"); break
                    case MediaPlayer.Loaded:
                        console.log("Video status:", "Loaded");
                        video.pause() // force to load video and show first frame
                        break
                    case MediaPlayer.Buffering:     console.log("Video status:", "Buffering"); break
                    case MediaPlayer.Stalled:       console.log("Video status:", "Stalled"); break
                    case MediaPlayer.Buffered:      console.log("Video status:", "Buffered"); break
                    case MediaPlayer.EndOfMedia:    console.log("Video status:", "EndOfMedia"); break
                    case MediaPlayer.InvalidMedia:  console.log("Video status:", "InvalidMedia"); break
                    case MediaPlayer.UnknownStatus: console.log("Video status:", "UnknownStatus"); break
                    }
                }*/
                function playback() {
                    if (playbackState == MediaPlayer.PlayingState)
                        pause()
                    else
                        play()
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: video.playback()
                }
            }

            VideoButtons {
                id: btnsVideo
                video: video
                onSeekDown: root.seekDown()
                onSeekUp: root.seekUp()
                onUndock: root.state = "undock"
            }
        }
    }

    state: "dock"
    states: [
        State {
            name: "dock"
            PropertyChanges {
                target: window
                visible: false
            }
            PropertyChanges {
                target: btnsVideo
                isUndock: false
            }
            PropertyChanges {
                target: btnClose
                visible: root.showClose
            }
            ParentChange {
                target: container
                parent: root
            }
        },
        State {
            name: "undock"
            PropertyChanges {
                target: window
                visible: true
            }
            PropertyChanges {
                target: undockContainer
                focus: true
            }
            PropertyChanges {
                target: btnsVideo
                isUndock: true
            }
            PropertyChanges {
                target: btnClose
                visible: false
            }
            ParentChange {
                target: container
                parent: undockContainer
            }
        }
    ]

    ApplicationWindow {
        id: window
        title: "Video"
        color: "black"
        width: Screen.desktopAvailableWidth / 2
        height: Screen.desktopAvailableHeight / 2
        x: Screen.desktopAvailableWidth / 2 - 5
        y: Screen.desktopAvailableHeight / 2 - 5

        onClosing: root.state = "dock"

        Item {
            id: undockContainer
            anchors.fill: parent

            // Hold focus here
            Keys.onRightPressed: root.seekUp()
            Keys.onLeftPressed: root.seekDown()
            Keys.onSpacePressed: root.pause()
        }
    }
}
