import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Styles 1.4
import QtQml.Models 2.15 // DelegateModel

import "../components"


// ListView with dragable buttons
Item {

    id: root
    property var model
    signal click(var path)

    GroupBoxDefault {

        padding: 7.5
        anchors.fill: parent
        title: "Folders"

        ListView {

            id: view
            anchors.fill: parent
            spacing: 5

            model: DelegateModel {
                id: visualModel
                model: root.model
                delegate: DropArea {

                    id: delegateRoot
                    width: root.width - 15
                    height: 30
                    property int itemIndex: DelegateModel.itemsIndex // index from model

                    onEntered: {
                        // Start move animation
                        visualModel.items.move((drag.source as ButtonDraggable).itemIndex, btn.itemIndex)
                    }

                    ButtonDraggable {
                        id: btn
                        width: delegateRoot.width
                        height: delegateRoot.height

                        dragParent: view
                        itemIndex: delegateRoot.itemIndex
                        text: model.name
                        onClick: root.click(model.path)
                        onMoveItem: root.model.move(key, target)
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
