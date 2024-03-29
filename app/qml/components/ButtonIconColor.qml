import QtQuick
import QtQuick.Controls

// Icon button with differet background colors
ButtonIcon {

    property bool backgroundState

    background: BackgroundDefault {

        colorDefault: backgroundState ? "transparent" : "whitesmoke"
        colorHovered: backgroundState ? "transparent" : "#e0e0e0" // light gray
        colorPressed: backgroundState ? "grey" : "white"
        border.color: backgroundState ? (parent.hovered ? "white" : "transparent") : "transparent"
    }
}
