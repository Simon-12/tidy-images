import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQml.Models 2.15 // DelegateModel

import "../components"


// Gallery main item
Item {

    id: root
    anchors.fill: parent
    property var model
    property int bufferSize
    property int gridIndex
    property bool isFullscreen: state === "fullscreen"
    property alias view: swipeView

    GridView {

        id: gridView
        anchors.fill: parent
        anchors.margins: 10
        cellWidth: 200
        cellHeight: 200
        interactive: false

        ScrollBar.vertical: ScrollBar {
            id: scrollbar
            width: 7
        }

        // Animation of item movement
        displaced: Transition {
            NumberAnimation { properties: "x,y"; duration: 400; easing.type: Easing.OutQuad }
        }

        // Remove animation
        remove: Transition {
            NumberAnimation { properties: "width,height"; to: 0; duration: 400 }
        }

        model: DelegateModel {
            id: visualModel
            model: root.model
            delegate: DropArea {

                id: delegateRoot
                width: gridView.cellWidth - 10
                height: gridView.cellHeight - 10
                property int itemIndex: DelegateModel.itemsIndex // index from model

                // Start move animation
                onEntered: visualModel.items.move(drag.source.itemIndex, delegateRoot.itemIndex)

                Loader {
                    anchors.fill: parent
                    active: Math.abs(gridView.currentIndex - index) < (root.bufferSize * 2)
                    sourceComponent: Pane {
                        id: pane
                        width: delegateRoot.width
                        height: delegateRoot.height
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        Material.elevation: 5
                        padding: 0

                        // Item background
                        Rectangle {
                            anchors.fill: parent
                            property color cDefault: "transparent"
                            property color cHovered: "#e0e0e0" // light gray
                            property color cpressed: "gray"
                            property color cSelected: "#9FA8DA" // indigo (shade)
                            color: area.pressed ? cpressed :
                                                  area.hovered ? cHovered :
                                                                 checkBox.checked ? cSelected : cDefault
                        }

                        FileItem {
                            id: fileItem
                            anchors.fill: parent
                            anchors.margins: 10
                            type: model.type
                            path: model.path
                            duration: model.duration
                            frame: model.frame
                            sourceSize: Qt.size(width, height)
                        }

                        MouseArea {
                            id: area
                            anchors.fill: parent
                            hoverEnabled: true
                            property bool hovered: false
                            drag.target: pane // drag target

                            onEntered: hovered = true
                            onExited: hovered = false
                            onClicked: {
                                root.gridIndex = index
                                var point = gridView.mapFromItem(pane, pane.x, pane.y)
                                fullscreen.x = point.x + 100
                                fullscreen.y = point.y + 100
                                root.state = "fullscreen"
                            }
                            onWheel: {
                                if(wheel.angleDelta.y > 0) scrollbar.decrease()
                                if(wheel.angleDelta.y < 0) scrollbar.increase()
                            }
                        }

                        CheckBox {
                            id: checkBox
                            visible: checked || hovered || area.hovered
                            width: 40
                            height: 40
                            padding: 0
                            verticalPadding: 0
                            anchors.top: parent.top
                            anchors.left: parent.left
                            checked: model.selected
                            onClicked: model.selected = checked
                        }

                        ButtonIcon {
                            state: model.favorite
                            visible: state || hovered || area.hovered
                            anchors.top: parent.top
                            anchors.right: parent.right
                            anchors.margins: 3
                            icon.source: state ? "qrc:/icons/flaticon/star_1.png" : "qrc:/icons/flaticon/star_2.png"
                            onClicked: root.model.favorite(index) // emit signal

                            background: BackgroundDefault {
                                radius: width
                                colorDefault: "transparent"
                                border.color: "transparent"
                            }
                        }

                        Drag.active: area.drag.active
                        Drag.source: delegateRoot // drag source
                        Drag.hotSpot.x: pane.width / 2
                        Drag.hotSpot.y: pane.height / 2

                        states: [
                            State {
                                when: area.drag.active
                                ParentChange {
                                    target: pane
                                    parent: gridView
                                }
                                AnchorChanges {
                                    target: pane
                                    anchors.horizontalCenter: undefined
                                    anchors.verticalCenter: undefined
                                }
                            }
                        ]

                    }
                }
            }
        }
    }

    // Main background
    Rectangle {
        id: backgroundRoot
        anchors.fill: parent
        color: "whitesmoke"

        MouseArea {
            anchors.fill: parent
            onClicked: root.state = "grid"
        }
    }

    // Fullscreen view
    Pane {
        id: fullscreen
        property int mW: backgroundRoot.width / 1.5
        property int mH: backgroundRoot.height / 1.5
        property int mX: backgroundRoot.width / 2 - mW / 2
        property int mY: backgroundRoot.height / 2 - mH / 2
        width: 0
        height: 0
        Material.elevation: 5

        SwipeFileView {
            id: swipeView
            anchors.fill: parent
            model: root.model
            bufferSize: visible ? root.bufferSize : 0
        }
    }

    state: "grid"
    states: [
        State {
            name: "grid"
            PropertyChanges { target: backgroundRoot; visible: false; opacity: 0 }
            PropertyChanges { target: fullscreen; visible: false; width: 0; height: 0 }
        },
        State {
            name: "fullscreen"
            PropertyChanges { target: backgroundRoot; visible: true; opacity: 0.75 }
            PropertyChanges { target: fullscreen; visible: true;
                width: fullscreen.mW; height: fullscreen.mH; x: fullscreen.mX; y: fullscreen.mY}
        }
    ]
    transitions: [
        Transition {
            from: "grid"; to: "fullscreen"
            NumberAnimation { target: fullscreen; properties: "width,height,x,y"; duration: 500 }
            OpacityAnimator { target: backgroundRoot; duration: 500 }
        }
    ]
}
