import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

// Default RoundButton
RoundButton {

    height: parent.height - 5
    width: height

    topInset: 0
    leftInset: 0
    rightInset: 0
    bottomInset: 0
    padding: 0

    font.pointSize: 12
    Material.elevation: 1
}
