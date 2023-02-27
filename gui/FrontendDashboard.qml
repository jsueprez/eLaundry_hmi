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

        Rectangle{
            id: pathViewBackground
            width: 400 // magic numbers
            height: 400 // magic numbers
            anchors.left: backgroundChoose.right
            anchors.leftMargin: 40
            anchors.verticalCenter: parent.verticalCenter
            color: "#8e8b93"
            radius: 20

            Component  {
                id : delegate
                Column {
                    id: wrapper
                    opacity: PathView.isCurrentItem ? 1 : 0.5
                    Image {
                        anchors.horizontalCenter: nameText.horizontalCenter
                        width: 100; height: 100
                        source: icon
                    }
                    Text {
                        id: nameText
                        text: name
                        font.pointSize: 16
                    }
                }
            }

            PathView {
                anchors.fill: parent
                model: NovaLockerModel {}
                delegate : delegate
                focus : true

                path: Path {
                    startX: pathViewBackground.width / 2; startY: (pathViewBackground.height / 2) + 100 ;
                    PathAttribute { name: "iconScale"; value: 1.0 }
                    PathAttribute { name: "iconOpacity"; value: 1.0 }
                    PathQuad { x: (pathViewBackground.width / 2 + 100) ; y: (pathViewBackground.height / 2); controlX: (pathViewBackground.width / 2 + 100); controlY: 75 }
                    PathAttribute { name: "iconScale"; value: 0.3 }
                    PathAttribute { name: "iconOpacity"; value: 0.5 }
                    PathQuad { x: pathViewBackground.width / 2; y: (pathViewBackground.height / 2) + 100; controlX: -20; controlY: 75 }

                }
            }
        }
    }
}


