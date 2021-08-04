import QtQuick 2.15
import QtQuick.Controls 2.15


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
