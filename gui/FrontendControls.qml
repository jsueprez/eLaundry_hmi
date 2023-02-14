import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import "."

Item {
    id: frontendControls
    anchors.fill: parent

    onVisibleChanged: {
        backendControls.set_frontend(this)

        if (!visible) return
        background.opacity = 1.0
    }

    /* CONTAINER
     * This item is built based on layout.
     *  1st layout is the header, where connection icons are placed.
     *  2rd Layout is the footer, where the camera icon is placed
     */
    Rectangle {

        id: background
        property alias backgroundCenter : background.horizontalCenter

        anchors.fill: parent
        color: "black"

        ColumnLayout{
            anchors.fill: parent
            spacing: 0

            RowLayout {
                id: header_layout
                z:0
                spacing: 2
                Layout.maximumHeight: 40;
                width: parent.width

                Rectangle {
                    Layout.minimumWidth: 100;
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "black"

                    ItemConnection {
                        height: 40
                        width: 40
                        anchors.left: parent.left
                        anchors.leftMargin: 8
                        opacity: appWindow.connType != ELaundry.connectionNONE ? 1.0 : 0.0
                        visible: opacity > 0.01
                        Behavior on opacity { OpacityAnimator { duration: 200 } }
                    }
                }

                Rectangle {
                    Layout.minimumWidth: 200;
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: 'black'

                    Image {
                        id: mywallboxIcon
                        source: "images/mywallbox_connection.png"
                        width: 30
                        fillMode: Image.PreserveAspectFit
                        mipmap: true
                        sourceSize.width: 34
                        sourceSize.height: 34
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.top: parent.top
                        anchors.topMargin: 5
                        opacity: appWindow.iconMyWallbox ? 1.0 : 0.0
                        visible: opacity > 0.01

                        Behavior on opacity { OpacityAnimator { duration: 200 } }
                    }

//                    IconTime {
//                        id: timeIcon
//                        width: 40; height: 40
//                        colorForeground: Wallbox.colorGREY
//                        anchors.right: mywallboxIcon.left
//                        anchors.rightMargin: 5
//                        opacity: appWindow.iconScheduled ? 1.0 : 0.0
//                        visible: opacity > 0.01
//                        Behavior on opacity { OpacityAnimator { duration: 200 } }
//                    }

//                    IconPower {
//                        width: 36; height: 36
//                        colorForeground: Wallbox.colorGREY
//                        anchors.right: timeIcon.left
//                        anchors.rightMargin: 0
//                        anchors.top: parent.top
//                        anchors.topMargin: 2
//                        opacity: appWindow.iconPowerBoost ? 1.0 : 0.0
//                        visible: opacity > 0.01
//                        Behavior on opacity { OpacityAnimator { duration: 200 } }
//                    }
                }
            }

            RowLayout {
                id: body_layout
                z: 2
                spacing: 2
                Layout.maximumHeight: 192;
                width: parent.width

                Rectangle {
                    Layout.minimumWidth: 100;
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "black"

                }
            }

            RowLayout {
                id: footer_layout
                z:1
                spacing: 2
                Layout.maximumHeight: 40;
                width: parent.width

                Rectangle {
                    Layout.minimumWidth: 200;
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: 'black'

                    Image {
                        source: "images/camera.png"
                        width: 30
                        fillMode: Image.PreserveAspectFit
                        mipmap: true
                        sourceSize.width: 55
                        sourceSize.height: 44
                        anchors.right: parent.right
                        anchors.rightMargin: 14
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 10
                        opacity: appWindow.iconFaceRecognition ? 1.0 : 0.0
                        visible: opacity > 0.01
                        Behavior on opacity { OpacityAnimator { duration: 200 } }
                    }
                }
            }
        }
    }
}
