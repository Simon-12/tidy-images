import QtQuick
import QtQuick.Controls

// Focus handler
Item {

    id: root
    focus: true
    property bool state: false

    function checkFocus(activeItem) {
        if (activeItem === null)
            return
        var name = activeItem.objectName
        // console.log(name) // debug
        if (name === "item unlock")
            root.state = true
        if (name === "item lock")
            root.state = false
        if (root.state)
            return
        else
            root.forceActiveFocus() // hold focus here
    }
}
