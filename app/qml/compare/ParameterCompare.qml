import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

// Compare parameters
Column {

    id: root
    property alias threshold: thresholdBox.value
    property alias image: left.checked
    spacing: 10

    Row {
        spacing: 20

        Label {
            width: 140
            height: 40
            text: "Select Image:"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
        }

        // Button group with checkboxes
        ButtonGroup {
            id: buttonGroup
        }
        CheckBox {
            id: left
            width: 90
            height: 40
            text: "Left"
            checked: true
            ButtonGroup.group: buttonGroup
        }
        CheckBox {
            width: 90
            height: 40
            text: "Right"
            ButtonGroup.group: buttonGroup
        }
    }

    Row {
        spacing: 20

        Label {
            width: 140
            height: 40
            text: "Score Threshold:"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
        }

        SpinBox {
            id: thresholdBox
            width: 150
            height: 40
            from: 1
            to: 100
            editable: true
        }
    }
}
