import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import qml.components
import "../components"

// Popup with infos about the application
PopupDefault {

    id: root
    width: 400
    height: 350

    property int textWidth: 270

    onOpened: bar.currentIndex = 0

    function openWebsite() {
        Qt.openUrlExternally(info.website)
    }

    ApplicationInfo {
        id: info
    }

    ColumnLayout {
        anchors.fill: parent

        StackLayout {
            currentIndex: bar.currentIndex

            // About page
            RowLayout {
                spacing: 15
                // Icon left side
                ImageDefault {
                    Layout.preferredWidth: 75
                    Layout.preferredHeight: 75
                    source: "qrc:/icons/flaticon/icon.png"
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    contentWidth: availableWidth
                    clip: true

                    ColumnLayout {
                        anchors.fill: parent
                        spacing: 15

                        // About
                        LabelLink {
                            Layout.preferredWidth: root.textWidth
                            textFormat: Text.RichText
                            verticalAlignment: Text.AlignTop
                            horizontalAlignment: Text.AlignLeft
                            text: info.about
                        }

                        // Donation buttons
                        RowLayout {
                            Layout.alignment: Qt.AlignHCenter
                            ButtonDefault {
                                implicitWidth: 100
                                onClicked: Qt.openUrlExternally(info.paypal)
                                ImageDefault {
                                    width: parent.width - 30
                                    height: width
                                    anchors.centerIn: parent
                                    source: "qrc:/icons/flaticon/paypal.png"
                                }
                            }
                            ButtonDefault {
                                implicitWidth: 100
                                onClicked: btc.open()
                                ImageDefault {
                                    width: parent.width - 30
                                    height: width
                                    anchors.centerIn: parent
                                    source: "qrc:/icons/flaticon/bitcoin.png"
                                }
                            }
                        }

                        // Story and links
                        LabelLink {
                            Layout.preferredWidth: root.textWidth
                            textFormat: Text.RichText
                            verticalAlignment: Text.AlignTop
                            horizontalAlignment: Text.AlignLeft
                            text: info.story
                        }
                    }
                }
            }

            // License page
            RowLayout {
                spacing: 15
                // Icon left side
                ImageDefault {
                    Layout.preferredWidth: 75
                    Layout.preferredHeight: 75
                    source: "qrc:/icons/flaticon/icon.png"
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    contentWidth: availableWidth
                    clip: true
                    LabelLink {
                        width: root.textWidth
                        text: info.license
                        verticalAlignment: Text.AlignTop
                        horizontalAlignment: Text.AlignLeft
                    }
                }
            }

            // Qt page
            RowLayout {
                spacing: 10
                ImageDefault {
                    Layout.preferredWidth: 75
                    Layout.preferredHeight: 75
                    source: "qrc:/icons/qt.png"
                }
                ScrollView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    contentWidth: availableWidth
                    clip: true
                    LabelLink {
                        width: root.textWidth
                        text: info.qtinfo
                        verticalAlignment: Text.AlignTop
                        horizontalAlignment: Text.AlignLeft
                    }
                }
            }

            // Icon page
            ScrollView {
                clip: true
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                Column {
                    anchors.fill: parent
                    spacing: 15

                    Row {
                        width: parent.width
                        Label {
                            text: "Font"
                            width: 50
                            height: 30
                            font.bold: true
                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter
                        }
                        LabelLink {
                            width: 150
                            height: 30
                            text: info.font
                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    Label {
                        text: "Icons"
                        width: parent.width
                        font.bold: true
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                    }
                    ListView {
                        id: view
                        spacing: 7
                        clip: true
                        interactive: false
                        width: parent.width
                        height: contentHeight

                        model: info.model
                        delegate: Pane {
                            width: view.width
                            height: 30
                            padding: 0
                            Material.elevation: 5

                            RowLayout {
                                anchors.fill: parent
                                anchors.leftMargin: 10
                                anchors.rightMargin: 30
                                ImageDefault {
                                    Layout.preferredWidth: 20
                                    Layout.preferredHeight: 20
                                    source: model.icon
                                }
                                Item {
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: 20
                                    LabelLink {
                                        showTooltip: true
                                        anchors.centerIn: parent
                                        text: model.name
                                    }
                                }
                                LabelLink {
                                    showTooltip: true
                                    text: model.author
                                }
                            }
                        }
                    }
                }
            }
        }

        TabBar {
            id: bar
            Layout.preferredWidth: parent.width
            position: TabBar.Footer

            TabButton {
                text: "About"
                font.capitalization: Font.MixedCase
            }
            TabButton {
                text: "License"
                font.capitalization: Font.MixedCase
            }
            TabButton {
                text: "Qt"
                font.capitalization: Font.MixedCase
            }
            TabButton {
                text: "References"
                font.pointSize: 10
                font.capitalization: Font.MixedCase
            }
        }
    }

    PopupDefault {
        id: btc
        onOpened: address.objectName = "item unlock"
        onClosed: address.objectName = "item lock"

        Column {
            anchors.fill: parent
            spacing: 10

            ImageDefault {
                width: 320
                height: width
                source: "qrc:/bitcoin-code.png"
            }
            TextField {
                id: address
                objectName: "item lock" // Needed for focus check
                width: parent.width
                topPadding: 0
                bottomPadding: 10
                font.pointSize: 10
                font.bold: true
                selectByMouse: true
                text: info.btc
            }
        }
    }
}
