import QtQuick
import QtQuick.Controls

// Compare table
Row {

    id: root
    property var model

    TableView {
        id: table
        width: 605
        height: 130

        columnSpacing: 10
        rowSpacing: 1
        clip: true
        interactive: false

        model: root.model

        delegate: Rectangle {

            implicitWidth: model.column === 0 ? 75 : 250
            implicitHeight: 25
            border.width: 1
            border.color: (model.column === 0
                           || model.row === 0) ? "transparent" : "black"
            color: model.color

            Text {
                text: model.text
                font.bold: model.column === 0 || model.row === 0
                font.pointSize: 12
                anchors.centerIn: parent
            }
        }
    }

    // Freespace for centering
    Item {
        width: 75
        height: 1
    }
}
