import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "."

Item {
    id: frontendDashboard
    height: 272
    width: 230

    property string power: "0.0"
    property string userAmperes: "6"

    onVisibleChanged: {
        backendDashboard.set_frontend(this)

        if (!visible) return
        background.opacity = 1.0
    }

    /* CONTAINER
     * This item is built based on layout.
     *  1st layout is the header, where connection icons are placed.
     *  2nd Layout is the body, where the halo item is placed
     *  3rd Layout is the footer, where the camera icon is placed
     */
    Rectangle {

        id: background
        property alias backgroundCenter : background.horizontalCenter

        anchors.fill: parent
        color: "black"

        ItemHalo{
            z: 1
            width: 224
            height: 224
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}


