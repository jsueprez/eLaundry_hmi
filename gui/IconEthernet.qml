import QtQuick 2.5
import QtQuick.Controls 2.0
import "."

Item {

    property real lineOut: 2
    property real lineIn: 1

    property color colorBackground: ELaundry.colorWHITE
    property color colorForeground: ELaundry.colorGREY

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()

            ctx.lineCap = "round"
            ctx.lineJoin = "round"

            ctx.strokeStyle = colorForeground
            ctx.fillStyle = colorForeground

            // outter rect
            ctx.lineWidth = lineOut

            ctx.beginPath()
            ctx.roundedRect(Math.round(width * 0.20), Math.round(height * 0.20), Math.round(width * 0.60), Math.round(height * 0.60), width * 0.10, height * 0.10)
            ctx.stroke()

            // inner rect
            ctx.lineWidth = lineIn

            ctx.beginPath()
            ctx.roundedRect(Math.round(width * 0.30), Math.round(height * 0.30), Math.round(width * 0.40), Math.round(height * 0.30), width * 0.06, height * 0.06)
            ctx.fill()

            ctx.beginPath()
            ctx.roundedRect(Math.round(width * 0.42), Math.round(height * 0.50), Math.round(width * 0.16), Math.round(height * 0.16), width * 0.03, height * 0.03)
            ctx.fill()

            ctx.fillStyle = colorBackground

            ctx.beginPath()
            ctx.roundedRect(Math.round(width * 0.42) + lineIn, Math.round(height * 0.50) + lineIn, Math.round(width * 0.16) - 2*lineIn, Math.round(height * 0.16) - 2*lineIn, width * 0.03, height * 0.03)
            ctx.fill()

            ctx.beginPath()
            ctx.roundedRect(Math.round(width * 0.30) + lineIn, Math.round(height * 0.30) + lineIn, Math.round(width * 0.40) - 2*lineIn, Math.round(height * 0.30) - 2*lineIn, width * 0.06, height * 0.06)
            ctx.fill()

            for (var i = 0; i < 4; ++i)
            {
                ctx.beginPath()
                ctx.moveTo(width * (0.395 + i * 0.07), height * 0.30 + lineIn)
                ctx.lineTo(width * (0.395 + i * 0.07), height * 0.36 + lineIn)
                ctx.stroke()
            }
        }
    }
}
