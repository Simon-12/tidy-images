import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// Popup with progressbar
PopupDefault {

    id: root
    width: 600
    height: 90

    property bool show
    property int size
    property int progress
    property string text

    onShowChanged: {
        if (show)
            open()
        else
            close()
    }

    ColumnLayout {

        anchors.fill: parent

        Label {
            text: root.text
            font.pointSize: 14
            font.bold: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: parent.height / 2
        }

        ProgressBar {
            id: progress
            from: 0
            to: root.size
            value: root.progress
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
