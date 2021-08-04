import QtQuick 2.15
import QtQuick.Controls 2.15

import "../components"


// Image main item
Item {

    id: root
    property string source
    property alias fillMode: image.fillMode
    property alias sourceSize: image.sourceSize
    signal clicked()
    signal indexUp()
    signal indexDown()
    signal imageLoaded()

    onSourceChanged: {
        if(!source)
            image.source = "" // undefined
        else
            image.source = source
    }

    ImageDefault {

        id: image
        anchors.centerIn: parent
        width: ( rotation == 90 || rotation == 270 ) ? parent.height : parent.width
        height: ( rotation == 90 || rotation == 270 ) ? parent.width : parent.height

        onStatusChanged: {
            if (status == Image.Ready)
                root.imageLoaded()
        }

        // Load info
        Column {
            anchors.centerIn: parent
            spacing: 10
            visible: root.width > 50

            BusyIndicator {
                width: parent.width // Fit to label
                running: image.status != Image.Ready
            }
            Label {
                visible: image.status != Image.Ready
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 14
                text: "Load Image ..."
            }
        }

        // Scroll Area
        MouseArea {
            anchors.fill: parent

            onDoubleClicked: root.clicked()
            onWheel: {
                if(wheel.angleDelta.y > 0) root.indexUp()
                if(wheel.angleDelta.y < 0) root.indexDown()
            }
        }
    }

    // Rotate image in given direction
    function setRotation(direction) {
        if(direction)
        {
            image.rotation += 90
            if(image.rotation == 360)
                image.rotation = 0
        }
        else
        {
            image.rotation -= 90
            if(image.rotation < 0)
                image.rotation = 270
        }
    }
}
