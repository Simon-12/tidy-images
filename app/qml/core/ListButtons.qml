import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQml.Models

import "../components"

// ListView with dragable buttons
Item {

    id: root
    property var model
    property int sizeModel: model !== null ? model.size : 0
    signal click(string path)
    signal addFolder

    GroupBoxDefault {

        padding: 7.5
        anchors.fill: parent
        title: "Folders"

        ButtonDefault {
            anchors.fill: parent
            icon.source: "qrc:/icons/flaticon/add.png"
            onClicked: root.addFolder()
            visible: sizeModel == 0
        }

        ListView {

            id: view
            anchors.fill: parent
            spacing: 5
            visible: sizeModel > 0

            model: DelegateModel {
                id: visualModel
                model: root.model
                delegate: DropArea {

                    id: delegateRoot
                    width: root.width - 15
                    height: 30
                    property int itemIndex: DelegateModel.itemsIndex // index from model

                    onEntered: function (drag) {
                        // Start move animation
                        visualModel.items.move(
                                    (drag.source as ButtonDraggable).itemIndex,
                                    btn.itemIndex)
                    }

                    ButtonDraggable {
                        id: btn
                        width: delegateRoot.width
                        height: delegateRoot.height

                        dragParent: view
                        itemIndex: delegateRoot.itemIndex
                        text: model.name
                        onClick: root.click(model.path)
                        onMoveItem: (key, target) => root.model.move(key,
                                                                     target)
                    }
                }
            }

            // Animation of item movement
            displaced: Transition {
                NumberAnimation {
                    properties: "x,y"
                    duration: 200
                    easing.type: Easing.OutQuad
                }
            }
        }
    }
}
