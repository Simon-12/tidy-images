import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12


// Default RoundButton
RoundButton {

    height: parent.height - 2
    width: height

    topInset: 0
    leftInset: 0
    rightInset: 0
    bottomInset: 0
    padding: 0

    font.pointSize: 12
    Material.elevation: 1
}
