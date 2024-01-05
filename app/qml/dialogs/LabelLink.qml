import QtQuick
import QtQuick.Controls

// Label with link and tooltip
Label {

    property bool showTooltip: false

    font.pointSize: 10
    wrapMode: Text.WordWrap
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignHCenter

    onLinkActivated: link => Qt.openUrlExternally(link)
    onHoveredLinkChanged: function (link) {
        if (!showTooltip)
            return
        if (link === "")
            tooltip.visible = false
        else {
            tooltip.visible = true
            label.text = link
        }
    }

    Rectangle {
        id: tooltip
        width: label.width + 5
        height: label.height + 2
        anchors.centerIn: parent
        visible: false
        color: "#e0e0e0" // lightgrey
        border.color: "black"
        border.width: 1

        Label {
            id: label
            anchors.centerIn: parent
            font.pointSize: 8
        }
    }
}
