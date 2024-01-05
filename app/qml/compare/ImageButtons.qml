import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import "../components"
import "../core"

// Image swipewview with buttons
Item {

    id: root
    property var model
    property int index
    property int bufferSize
    signal imageLoaded(int image)
    signal btnDelete

    ColumnLayout {

        anchors.fill: parent
        spacing: 10

        Pane {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Material.elevation: 5

            SwipeImageView {
                id: swipeView
                model: root.model
                bufferSize: root.bufferSize
                onNewIndex: index => root.index = index
                onImageLoaded: image => root.imageLoaded(image)
            }
        }

        Row {

            Layout.preferredWidth: 160
            Layout.preferredHeight: 40
            Layout.alignment: Qt.AlignHCenter
            Layout.bottomMargin: 10
            spacing: 5

            ButtonDefault {
                width: parent.height
                height: parent.height
                iconSize: 22
                icon.source: "qrc:/icons/material/back.png"
                onClicked: swipeView.indexDown()
            }

            ButtonDefault {
                width: parent.height
                height: parent.height
                icon.source: "qrc:/icons/flaticon/trash.png"
                onClicked: root.btnDelete()
            }

            ButtonDefault {
                width: parent.height
                height: parent.height
                iconSize: 22
                icon.source: "qrc:/icons/material/next.png"
                onClicked: swipeView.indexUp()
            }
        }
    }
}
