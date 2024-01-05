import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import "../components"
import "../dialogs"

// Popup with compare parameters
PopupDefault {

    id: root
    property int size: 0
    property int progress
    property int threshold
    signal startCompare(bool image, int threshold)
    signal stopCompare

    onProgressChanged: {
        if (progress === 0) {
            label.text = "---"
            return
        }
        if (progress === root.size)
            btn.btnState = true
        label.text = progress.toString() + " / " + root.size.toString()
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        // First Row
        RowLayout {
            spacing: 20

            // First Column
            ButtonDefault {
                id: btn
                iconSize: 18
                implicitWidth: 200
                implicitHeight: 36

                property bool btnState: true
                state: btnState ? "start" : "stop"
                onPressed: btnState = !btnState
                onClicked: btnState ? root.stopCompare() : root.startCompare(
                                          parameter.image, parameter.threshold)

                states: [
                    State {
                        name: "start"
                        PropertyChanges {
                            target: btn
                            text: "Start Compare"
                            icon.source: "qrc:/icons/flaticon/play.png"
                        }
                    },
                    State {
                        name: "stop"
                        PropertyChanges {
                            target: btn
                            text: "Stop Compare"
                            icon.source: "qrc:/icons/flaticon/stop.png"
                        }
                    }
                ]
            }
            // Second Column
            ParameterCompare {
                id: parameter
                threshold: root.threshold
            }
        }

        Rectangle {
            Layout.preferredWidth: parent.width
            Layout.preferredHeight: 2
            color: "black"
        }

        // Second Row
        RowLayout {
            Label {
                id: label
                Layout.preferredWidth: 150
                Layout.preferredHeight: parent.height
                text: "---"
                font.bold: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
            ProgressBar {
                id: bar
                Layout.fillWidth: true
                implicitHeight: 75
                from: 0
                to: root.size
                value: root.progress
            }
        }
    }
}
