import QtQuick 2.5
import QtQuick.Controls 2.0
import "."

Item {
    id: frontendControlsUI

    property alias nova: novaLogo.visible
    property alias barTop: barTop

    x: appWindow.mainAreaX
    width: appWindow.mainAreaW
    height: parent.height

    Item {
        id: barTop
        width: parent.width

        Row {
            x: 12; y: 2

            ItemConnection {
                y: 4; width: 40; height: 40
                opacity: 1.0
                visible: opacity > 0.01

                Behavior on opacity { OpacityAnimator { duration: 200 } }
            }

            IconBluetooth {
                y: 4; width: 30; height: 40
                opacity: 1.0
                visible: opacity > 0.01

                Behavior on opacity { OpacityAnimator { duration: 200 } }
            }

            move: Transition {
                NumberAnimation { properties: "x"; easing.type: Easing.Bezier; easing.bezierCurve: Wallbox.curveStd; duration: 200 }
            }
        }

        Image {
            id: novaLogo
            source: "images/novaLogo.png"
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            width: 140
            fillMode: Image.PreserveAspectFit
        }
    }

    Label {
        id: clockText

        anchors.top: parent.top
        anchors.topMargin: 15
        anchors.right: parent.right
        anchors.rightMargin:  20

        font.pixelSize: 18
        font.letterSpacing: 2
        color: ELaundry.colorGREY

        Timer {
            interval: 10000; running: true; repeat: true; triggeredOnStart: true
            onTriggered: clockText.text = backendControlsUI.now()
        }
    }
}

