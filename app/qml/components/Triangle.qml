import QtQuick 2.15
import QtQuick.Controls 2.15


// Self painted triangle button with Canvas
Item {

    id: root
    signal clicked()
    property int triangleWidth: 40
    property int triangleHeight: 48
    property color cDefault: "gray"
    property color cHovered: "#e0e0e0" // light gray
    property color cpressed: "white"
    property color currentColor: area.pressed ? cpressed :
                                                area.hovered ? cHovered : cDefault
    onCurrentColorChanged: triangle.requestPaint()

    Canvas {

        id: triangle
        width: triangleWidth + 20
        height: triangleHeight + 20
        anchors.centerIn: parent
        opacity: 0.7

        onPaint: {
            var ctx = getContext("2d")
            ctx.save();
            ctx.clearRect(0, 0, triangle.width, triangle.height);

            // put in the middle
            ctx.beginPath();
            ctx.translate((0.5 * width - 0.5 * triangleWidth),
                          (0.5 * height - 0.5 * triangleHeight))

            // the equliteral triangle
            ctx.moveTo(0, 0);
            ctx.lineTo(triangleWidth, triangleHeight / 2);
            ctx.lineTo(0, triangleHeight);
            ctx.closePath();

            // outline
            ctx.lineWidth = 3;
            ctx.strokeStyle = "black";
            ctx.stroke();

            // fill color
            ctx.fillStyle = currentColor;
            ctx.fill();
            ctx.restore();
        }

        MouseArea {
            id: area
            anchors.fill: parent
            hoverEnabled: true
            property bool hovered: false

            onEntered: hovered = true
            onExited: hovered = false
            onClicked: root.clicked()
        }
    }
}
