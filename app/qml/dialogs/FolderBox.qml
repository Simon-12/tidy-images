import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.12

import "../components"


// Delegate for folder dialog
Item {

    id: root

    property string name
    property string path
    property bool checked
    signal clicked()
    signal browse()
    signal remove()

    Pane {
        anchors.fill: parent
        Material.elevation: 5        
        leftPadding: 10
        rightPadding: 10
        padding: 0

        RowLayout {
            anchors.fill: parent
            spacing: 15

            CheckBox {
                padding: 0
                verticalPadding: 0
                checked: root.checked
                onClicked: root.clicked()
            }

            Label {
                text: root.name
                font.pointSize: 11
                font.bold: true
                Layout.preferredWidth: 140
            }

            TextField {
                Layout.fillWidth: true
                topPadding: 0
                bottomPadding: 0
                text: root.path
                font.pointSize: 9
                onAccepted: root.browse()
                onEditingFinished: text = root.path
                selectByMouse: true
            }

            ButtonIcon {
                onClicked: root.browse()
                icon.source: "qrc:/icons/flaticon/folder_search.png"
            }

            ButtonIcon {
                onClicked: root.remove()
                iconSize: 18
                icon.source: "qrc:/icons/flaticon/remove.png"
            }
        }
    }
}
