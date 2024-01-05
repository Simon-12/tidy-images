import QtQuick
import QtQuick.Controls

// Database header filter field
Item {

    id: root
    property string filter
    signal finished

    TextField {

        objectName: "item lock" // Needed for focus check
        anchors.fill: parent
        text: root.filter
        placeholderText: "Filter"
        selectByMouse: true
        leftPadding: 5
        rightPadding: 5
        topPadding: 0
        bottomPadding: 0

        background: Rectangle {
            color: "white"
            border.color: "black"
        }

        onTextChanged: root.filter = text
        onPressed: objectName = "item unlock"
        onAccepted: {
            objectName = "item lock"
            focus = false
            root.finished()
        }
    }
}
