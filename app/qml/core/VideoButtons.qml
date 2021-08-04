import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtMultimedia 5.15 // Video

import "../components"


// Video buttons on bottom position
ColumnLayout {

    id: root
    property Video video
    property bool isUndock
    property alias volume: volumeSld.value
    property alias label: label.text
    property alias play: playBtn.state
    signal seekUp()
    signal seekDown()
    signal undock()

    // Icon propertys
    property string iconPlay: isUndock ? "qrc:/icons/material/play_white.png" : "qrc:/icons/material/play.png"
    property string iconPause: isUndock ? "qrc:/icons/material/pause_white.png" : "qrc:/icons/material/pause.png"
    property string iconUp: isUndock ? "qrc:/icons/material/forward_white.png" : "qrc:/icons/material/forward.png"
    property string iconDown: isUndock ? "qrc:/icons/material/rewind_white.png" : "qrc:/icons/material/rewind.png"
    property string iconVolume: isUndock ? "qrc:/icons/material/volume_white.png" : "qrc:/icons/material/volume.png"
    property string iconMute: isUndock ? "qrc:/icons/material/mute_white.png" : "qrc:/icons/material/mute.png"

    // Duration slider row
    RowLayout {
        Layout.rightMargin: 10

        Slider {
            Layout.fillWidth: true
            implicitHeight: 20
            from: 0
            to: root.video.duration
            value: root.video.position
            onMoved: root.video.seek(value)
        }
        Label {
            id: label
            color: isUndock ? "white" : "black"
            font.pointSize: 12
            verticalAlignment: Text.AlignVCenter
        }
    }

    // Button row
    RowLayout {
        Layout.bottomMargin: 5
        Layout.leftMargin: 5
        spacing: 5

        ButtonIcon {
            visible: !root.isUndock
            icon.source: "qrc:/icons/material/launch.png"
            onClicked: root.undock()
        }

        Item {
            // Freespace
            Layout.fillWidth: true
        }

        Row {
            spacing: 10

            ButtonIconColor {
                backgroundState: root.isUndock
                icon.source: root.iconDown
                onClicked: root.seekDown()
            }
            ButtonIconColor {
                id: playBtn
                backgroundState: root.isUndock
                iconSize: 31
                icon.source: state ? root.iconPlay : root.iconPause
                onClicked: root.video.playback()
            }
            ButtonIconColor {
                backgroundState: root.isUndock
                icon.source: root.iconUp
                onClicked: root.seekUp()
            }
        }

        Item {
            // Freespace
            Layout.fillWidth: true
        }

        ButtonIconColor {
            id: volumeBtn
            backgroundState: root.isUndock
            icon.source: state ? root.iconVolume : root.iconMute
            onClicked: {
                if(state)
                    volumeSld.value = 0
                else
                    volumeSld.value = 0.5
            }
        }
        SliderCustom {
            id: volumeSld
            from: 0
            to: 1
            value: 0.8
            onValueChanged: {
                if(value == 0)
                    volumeBtn.state = false
                else
                    volumeBtn.state = true
            }
        }
    }
}
