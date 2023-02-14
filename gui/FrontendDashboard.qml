import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "."

Item {
    id: frontendDashboard
    height: 480
    width: 800

    //property string power: "0.0"

    onVisibleChanged: {
        backendDashboard.set_frontend(this)

        if (!visible) return
        background.opacity = 1.0
    }

    Rectangle {
        id: background
        anchors.fill: parent

        Image {
            width: 150
            height: 33
            anchors.left: parent.left
            anchors.top: parent.top
            source: "images/novaLogoTxt.png"
            anchors.leftMargin: 20
            anchors.topMargin: 20
            fillMode: Image.PreserveAspectFit
        }

        Rectangle {
            id: backgroundChoose
            x: 44
            y: 140
            width: 200
            height: 200

            Text {
                id: chooseMachine
                text: "Please select an"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 20
                anchors.leftMargin: 10
                textFormat: Text.RichText
            }

            Text {
                id: chooseMachine_dos
                text: "available machine..."
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: chooseMachine.left
                anchors.top: chooseMachine.bottom
                font.pixelSize: 20
                anchors.topMargin: 0
                textFormat: Text.RichText
                anchors.leftMargin: 0
            }
        }

        Rectangle {
            id: pathViewBackground
            width: 451
            height: 354
            color: "#8e8b93"
            radius: 20
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: backgroundChoose.right
            anchors.leftMargin: 40
        }
    }
}


