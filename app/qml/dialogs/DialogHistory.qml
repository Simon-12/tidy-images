import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.12

import "../components"


// Popup for history
PopupDefault
{
    id: root
    width: 670
    height: 600
    property var model
    property var index: !model ? 0 : model.index // null

    Column {
        // Main layout
        anchors.fill: parent
        spacing: 15

        Label {
            id: label
            text: "History"
            font.bold: true
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
        }

        ListView {
            id: view
            width: parent.width
            height: parent.height - label.height - 15
            spacing: 15
            clip: true

            ScrollBar.vertical: ScrollBar {
                id: scrollbar
                width: 7
            }

            model: root.model
            delegate: HistoryBox {
                width: view.width
                height: 28 + (17 * model.number)
                name: model.name
                folder: model.folder
                source: !model.target ? "" :  // undefined
                                 root.index >= index ? model.target : model.source
                empty: index === 0
                selected: root.index === index
                onClicked: root.model.clicked(index)
            }
        }
    }
}
