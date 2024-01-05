import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// Groupbox with specific frame and label
GroupBox {

    id: root

    label: RowLayout {

        // Custom label
        x: root.leftPadding
        spacing: 10

        ImageDefault {
            Layout.preferredWidth: 24
            Layout.preferredHeight: 24
            source: "qrc:/icons/flaticon/folder2.png"
        }

        Label {
            text: root.title
        }
    }

    background: Rectangle {
        // Custom background
        y: root.topPadding - root.bottomPadding
        width: parent.width
        height: parent.height - root.topPadding + root.bottomPadding
        color: "transparent"
        border.color: "lightgrey"
        border.width: 2
        radius: 2
    }
}
