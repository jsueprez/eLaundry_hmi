import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "."

Item {
    id: frontendDashboard
    anchors.fill:  parent

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
            id: logo
            width: 150
            height: 33
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.leftMargin: 20
            anchors.topMargin: 20
            source: "images/novaLogoTxt.png"
            fillMode: Image.PreserveAspectFit
        }

        Rectangle {
            id: backgroundChoose
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: logo.bottom
            anchors.topMargin: 100
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


        Rectangle{
            id: carrouselBackground
            width: 450 // magic numbers
            height: 400 // magic numbers
            anchors.left: backgroundChoose.right
            anchors.leftMargin: 80
            anchors.verticalCenter: parent.verticalCenter

            FrontendNovaLockersCarrousel {
                id: frontendNovaLockersCarrousel
                visible: true

            }

        }



    }
}


