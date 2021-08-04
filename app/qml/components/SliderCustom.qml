import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Controls.impl 2.15


// Customized slider
Slider {

    id: root
    implicitWidth: 100
    implicitHeight: 20

    // Custom  background
    background: Rectangle {
        x: root.leftPadding
        y: root.topPadding + (root.availableHeight - height) / 2
        width: root.availableWidth
        height: root.availableHeight
        color: Color.transparent(Material.accentColor, 0.33)

        Rectangle {
            x: 0
            y: (parent.height - height) / 2
            width: root.position * parent.width
            height: parent.height
            color: Material.accentColor
        }
    }

    // Invisble slider
    handle: Rectangle {
        visible: false
        x: root.leftPadding + root.visualPosition * (root.availableWidth - width)
        y: root.topPadding + root.availableHeight / 2 - height / 2
        implicitWidth: 26
        implicitHeight: 26
        radius: 13
    }
}
