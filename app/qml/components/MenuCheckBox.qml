import QtQuick
import QtQuick.Controls

// Menu item with checkbox
MenuDefault {

    id: root
    property bool mode
    signal clicked

    onTriggered: root.clicked()

    CheckBox {

        id: checkBox
        width: 26
        height: 26
        checked: mode
        onClicked: root.clicked()

        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.right
        anchors.horizontalCenterOffset: -width
    }
}
