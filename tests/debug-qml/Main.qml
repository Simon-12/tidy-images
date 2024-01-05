import QtQuick
import QtQuick.Window

import "app/qml/dialogs"

Window {

    width: 800
    height: 600
    visible: true
    title: "Debug"

    DialogSettings {
        id: dlgSettings
        path: ""
        folders: ""
        database: ""
        favorites: ""
        trash: ""
        databaseActive: false
    }

    Component.onCompleted: dlgSettings.open()
}
