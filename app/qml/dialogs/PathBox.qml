import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../components"


// Item with path and buttons
Item {

    id: root
    implicitWidth: 450
    implicitHeight: 45

    property string name
    property string icon
    property string path
    signal browse()

    Rectangle {

        anchors.fill: parent
        color: "transparent"
        border.color: "black"
        border.width: 1

        RowLayout {

            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            spacing: 15

            ImageDefault {
                source: root.icon
                Layout.preferredHeight: 26
                Layout.preferredWidth: 26
            }

            Label {
                text: root.name
                font.bold: true
                font.pointSize: 11
                verticalAlignment: Text.AlignVCenter
                Layout.preferredHeight: root.height
                Layout.preferredWidth: 85
            }

            TextField {
                text: root.path
                font.pointSize: 9
                onAccepted: root.browse()
                onEditingFinished: text = root.path
                selectByMouse: true
                Layout.fillWidth: true
            }

            ButtonIcon {
                onClicked: root.browse()
                icon.source: "qrc:/icons/flaticon/folder_search.png"
            }
        }
    }
}
