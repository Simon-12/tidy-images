import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.12

import "../components"
import "../core"


// Database main item
Item {

    id: root
    anchors.fill: parent
    property var databaseModel
    property var headerModel
    property var fileModel
    property int bufferSize
    property alias view: swipeView
    property var widthArray: [220, 120, 150, 80, 140, 90, 5, 5, 5] // Hide last columns

    // Main layout
    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 5

        // Tabble left side (fix width)
        ColumnLayout {
            spacing: 15

            // Header
            Row {
                spacing: 10

                Repeater {
                    model: root.headerModel
                    delegate: Column {

                        spacing: 5

                        HeaderButton {
                            width: root.widthArray[index]
                            height: 40
                            name: model.name
                            direction: model.direction
                            onClicked: model.direction = direction + 1
                        }

                        HeaderFilter {
                            width: root.widthArray[index]
                            height: 24
                            filter: model.filter
                            onFilterChanged: model.filter = filter
                            onFinished: root.headerModel.finishedFilter()
                        }
                    }
                }
            }

            // Table
            TableDatabase {
                id: table
                model: root.databaseModel
                widthArray: root.widthArray
                Layout.preferredWidth: 800
                Layout.fillHeight: true
                onClicked: swipeView.index = row
            }
        }

        // Reset button
        ButtonClose {
            Layout.topMargin: 45
            Layout.alignment: Qt.AlignTop
            onClicked: root.headerModel.resetFiler()
        }

        // Images right side (fill width)
        Pane {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.leftMargin: 5
            Material.elevation: 5

            SwipeFileView {
                id: swipeView
                anchors.fill: parent
                model: root.fileModel
                bufferSize: root.bufferSize
                onNewIndex: table.index = index
            }
        }
    }
}
