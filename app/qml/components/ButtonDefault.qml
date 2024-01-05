import QtQuick
import QtQuick.Controls

// Default button for the application
Button {

    property int iconSize: 21

    implicitWidth: 120
    implicitHeight: 35

    topInset: 0 // Inset for background
    bottomInset: 0
    horizontalPadding: 0
    padding: 0 // Space to border
    spacing: 8 // Space icon to text

    icon.height: iconSize
    icon.width: iconSize
    icon.color: "transparent"

    font.capitalization: Font.MixedCase
    hoverEnabled: true
    background: BackgroundDefault {}
}
