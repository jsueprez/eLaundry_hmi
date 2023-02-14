import QtQuick 2.5
import QtQuick.Controls 2.0
import "."

Item {
    id: iconLock

    signal closed

    property color color: ELaundry.colorLOCKED
    property bool opened: false

    onColorChanged : canvas.requestPaint();

    Behavior on color { ColorAnimation { duration: 200 } }

    Canvas {
        id: canvas

        // y position used during animation
        property real y1: 0.0
        // shackle's left leg point
        property real p1: 0.0
        // angle in degrees
        property real angleCanvas: 0.0
        // angle in rad
        property real angleShackle: 0.0
        onP1Changed: canvas.requestPaint()
        onY1Changed: canvas.requestPaint()
        onAngleShackleChanged: canvas.requestPaint()

        anchors.fill: parent

        transform: Rotation { origin.x: width * 0.6; origin.y: height * 0.7; angle: canvas.angleCanvas }

        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()

            ctx.strokeStyle = color
            ctx.lineWidth = 4

            ctx.save()
            ctx.translate(0, y1)

            // square
            ctx.beginPath()
            ctx.roundedRect(Math.round(width * 0.30), Math.round(height * 0.45), Math.round(width * 0.40), Math.round(height * 0.32), width * 0.05, width * 0.05)
            ctx.stroke()

            // shackle
            ctx.save()
            ctx.translate(width * 0.70, height * 0.45)
            ctx.rotate(angleShackle)

            // left lines
            ctx.beginPath()
            ctx.moveTo(-width * 0.35, -height * p1)
            ctx.lineTo(-width * 0.35, -height * 0.13)

            ctx.moveTo(-width * 0.28, -height * p1)
            ctx.lineTo(-width * 0.28, -height * 0.13)

            // right lines
            ctx.moveTo(-width * 0.12, 0.0)
            ctx.lineTo(-width * 0.12, -height * 0.13)

            ctx.moveTo(-width * 0.05, 0.0)
            ctx.lineTo(-width * 0.05, -height * 0.13)

            // top lines
            //ctx.beginPath()
            ctx.moveTo(-width * 0.16, -height * 0.17)
            ctx.lineTo(-width * 0.24, -height * 0.17)

            ctx.moveTo(-width * 0.16, -height * 0.24)
            ctx.lineTo(-width * 0.24, -height * 0.24)
            ctx.stroke()

            // left arcs
            ctx.beginPath()
            ctx.arc(-width * 0.23, -height * 0.12, width * 0.05, 3.1415, -1.5708, false)
            ctx.stroke()

            ctx.beginPath()
            ctx.arc(-width * 0.23, -height * 0.12, width * 0.12, 3.1415, -1.5708, false)
            ctx.stroke()

            // right arcs
            ctx.beginPath()
            ctx.arc(-width * 0.17, -height * 0.12, width * 0.05, -1.5708, 0.0, false)
            ctx.stroke()

            ctx.beginPath()
            ctx.arc(-width * 0.17, -height * 0.12, width * 0.12, -1.5708, 0.0, false)
            ctx.stroke()

            // close arc
            if (p1 > 0.01)
            {
                ctx.beginPath()
                ctx.arc(-width * 0.315, -height * p1, width * 0.035, -3.1415, 0.0, true)
                ctx.stroke()
            }

            ctx.restore()
            ctx.restore()
        }
    }

    states: [
        State {
            name: "CLOSED"
            when: !opened
            PropertyChanges { target: canvas; p1: 0.0 }
        },

        State {
            name: "OPENED"
            when: opened
            PropertyChanges { target: canvas; p1: 0.12 }
        }
    ]

    transitions: [
        Transition {
            to: "CLOSED"

            onRunningChanged: {

                if (!running)
                {
                    iconLock.closed()
                    instant = false
                    backendDashboard.on_locked_end();
                }
            }

            ParallelAnimation {
                SequentialAnimation {
                    PropertyAnimation { target: canvas; properties: "y1"; from: 0.0; to: Math.round(-height * 0.10); easing.type: Easing.InOutQuad; duration: 150 }
                    PropertyAnimation { target: canvas; properties: "y1"; from: Math.round(-height * 0.10); to: Math.round(+height * 0.05); easing.type: Easing.InOutQuad; duration: 200 }
                    PropertyAnimation { target: canvas; properties: "y1"; from: Math.round(+height * 0.05); to: 0.0; easing.type: Easing.InOutQuad; duration: 150}
                }
                SequentialAnimation {
                    PauseAnimation { duration: 150 }
                    PropertyAnimation { target: canvas; properties: "angleCanvas"; from:   0; to: +12; easing.type: Easing.InOutQuad; duration: 130 }
                    PropertyAnimation { target: canvas; properties: "angleCanvas"; from: +12; to: -22; easing.type: Easing.InOutQuad; duration: 070}
                    PropertyAnimation { target: canvas; properties: "angleCanvas"; from: -22; to:   0; easing.type: Easing.InOutQuad; duration: 150 }
                }
                SequentialAnimation {
                    PauseAnimation { duration: 150 }
                    PropertyAnimation { target: canvas; properties: "angleShackle"; from: 0.0; to: 0.4; easing.type: Easing.InOutQuad; duration: 130}
                    PropertyAnimation { target: canvas; properties: "angleShackle"; from: 0.4; to: 0.0; easing.type: Easing.InOutQuad; duration: 070 }
                }
                SequentialAnimation {
                    PauseAnimation { duration: 320 }
                    PropertyAnimation { target: canvas; properties: "p1"; easing.type: Easing.InOutQuad; duration: 60 }
                }

                PauseAnimation {
                    duration: 1000
                }
            }
        },

        Transition {
            to: "OPENED"
            PropertyAnimation { target: canvas; properties: "p1"; easing.type: Easing.InOutQuad; duration: 60 }
        }
    ]
}
