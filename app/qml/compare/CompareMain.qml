import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "../components"

// Compare main item
Item {

    id: root
    anchors.fill: parent
    property var images
    property var table
    property int progress
    property int bufferSize
    signal imageLoaded(int image)
    signal startCompare(int index)
    signal stopCompare
    signal btnDelete(int index)

    ButtonDefault {
        width: 200
        height: 40
        anchors.centerIn: parent
        anchors.verticalCenterOffset: parent.height / 2 - 30
        enabled: root.table !== null ? root.table.active : false
        text: "Compare Images"
        icon.source: "qrc:/icons/flaticon/compare.png"
        onClicked: {
            dlgCompare.size = root.images.size()
            dlgCompare.open()
        }
    }

    DialogCompare {
        id: dlgCompare
        progress: root.progress
        threshold: root.table !== null ? root.table.threshold : 0

        onStopCompare: root.stopCompare()
        onStartCompare: function (image, threshold) {
            var val = 0
            if (image === true)
                val = left.index
            else
                val = right.index
            root.table.threshold = threshold
            root.startCompare(val)
        }
    }

    ColumnLayout {

        anchors.fill: parent

        TableCompare {
            id: table
            model: root.table
            Layout.alignment: Qt.AlignHCenter

            function setFile() {
                if (root.table === null)
                    return
                root.table.setFile(left.index, right.index)
            }
        }

        Row {

            spacing: 10
            Layout.fillWidth: true
            Layout.fillHeight: true

            ImageButtons {
                id: left
                width: parent.width / 2 - 5
                height: parent.height
                model: root.images
                bufferSize: root.bufferSize
                onIndexChanged: table.setFile()
                onImageLoaded: image => root.imageLoaded(image)
                onBtnDelete: root.btnDelete(index)
            }

            ImageButtons {
                id: right
                width: parent.width / 2 - 5
                height: parent.height
                model: root.images
                bufferSize: root.bufferSize
                onIndexChanged: table.setFile()
                onImageLoaded: image => root.imageLoaded(image)
                onBtnDelete: root.btnDelete(index)
            }
        }
    }
}
