import QtQuick
import QtQuick.Controls

// Dragable button for ListView
Rectangle {

    id: root
    color: "transparent"
    property Item dragParent
    property string text
    property int itemIndex
    signal click
    signal moveItem(string key, int target)

    anchors {
        horizontalCenter: parent.horizontalCenter
        verticalCenter: parent.verticalCenter
    }

    ButtonDefault {
        anchors.fill: parent
        text: root.text
        opacity: dragHandler.active ? 0.6 : 1.0
        onClicked: root.click()
    }

    DragHandler {
        id: dragHandler

        // If dragging is over, check index and move
        property int startIndex
        onActiveChanged: {
            if (active)
                startIndex = root.itemIndex
            else if (startIndex !== root.itemIndex)
                root.moveItem(root.text, root.itemIndex)
        }
    }

    Drag.active: dragHandler.active
    Drag.source: root
    Drag.hotSpot.x: root.width / 2
    Drag.hotSpot.y: root.height / 2

    states: [
        State {
            when: dragHandler.active
            ParentChange {
                target: root
                parent: root.dragParent
            }
            AnchorChanges {
                target: root
                anchors.horizontalCenter: undefined
                anchors.verticalCenter: undefined
            }
        }
    ]
}
