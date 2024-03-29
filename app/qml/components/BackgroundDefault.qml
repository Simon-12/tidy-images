import QtQuick
import QtQuick.Controls

// Default background for buttons and other items
Rectangle {

    id: root
    property color colorDefault: "whitesmoke"
    property color colorHovered: "#e0e0e0" // light gray
    property color colorPressed: "white"

    border.color: "black"
    color: parent.pressed ? root.colorPressed : (parent.hovered ? root.colorHovered : root.colorDefault)
}
