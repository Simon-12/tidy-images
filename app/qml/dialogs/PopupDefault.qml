import QtQuick 2.15
import QtQuick.Controls 2.15


// Default Popup with settings
Popup
{
    modal: true
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    //anchors.centerIn: parent // Is buged: position changes 2 times
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
}
