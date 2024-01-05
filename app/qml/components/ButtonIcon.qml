import QtQuick
import QtQuick.Controls

// Icon button without text
ButtonDefault {

    property bool state: true

    iconSize: 27
    implicitWidth: 35
    implicitHeight: 35

    background: BackgroundDefault {
        border.color: "transparent"
    }
}
