import QtQuick 2.5
import QtQuick.Controls 2.0
import "."

Item {
    property color colorBackground: ELaundry.colorWHITE
    property color colorForeground: ELaundry.colorGREY

    property real line: 1.2

    onColorBackgroundChanged: canvas.requestPaint()
    onColorForegroundChanged: canvas.requestPaint()

    Behavior on colorBackground { ColorAnimation { duration: 200 } }
    Behavior on colorForeground { ColorAnimation { duration: 200 } }

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()

            ctx.lineCap = "round"
            ctx.lineJoin = "round"

            ctx.strokeStyle = colorForeground
            ctx.lineWidth = line * 4

            ctx.beginPath()
            ctx.moveTo(width * 0.25, height * 0.35)
            ctx.lineTo(width * 0.75, height * 0.63)
            ctx.lineTo(width * 0.50, height * 0.83)
            ctx.lineTo(width * 0.50, height * 0.17)
            ctx.lineTo(width * 0.75, height * 0.37)
            ctx.lineTo(width * 0.25, height * 0.65)
            ctx.stroke()

            ctx.strokeStyle = colorBackground
            ctx.lineWidth = line * 2

            ctx.beginPath()
            ctx.moveTo(width * 0.25, height * 0.35)
            ctx.lineTo(width * 0.75, height * 0.63)
            ctx.lineTo(width * 0.50, height * 0.83)
            ctx.lineTo(width * 0.50, height * 0.17)
            ctx.lineTo(width * 0.75, height * 0.37)
            ctx.lineTo(width * 0.25, height * 0.65)
            ctx.stroke()
        }
    }
}

