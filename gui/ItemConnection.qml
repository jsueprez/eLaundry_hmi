import QtQuick 2.5
import QtQuick.Controls 2.0
import "."

Item {
    id: itemConnection

    IconEthernet {
        id: iconEthernet

        anchors.fill: parent
        visible: appWindow.connType === ELaundry.connectionETH
    }

//    IconWifi {
//        id: iconWifi
//        anchors.fill: parent

//        strength: appWindow.connStrength
//        onStrengthChanged: {
//            console.log("CHANGING STRENGhT: ITEM CONNECTION"+ strength)
//        }

//        visible: appWindow.connType === Wallbox.connectionWIFI

//    }

    /*IconGSM {
        id: iconGSM

        anchors.fill: parent
        visible: appWindow.connType === Wallbox.connectionGSM

        line: 2
        colorForeground: Wallbox.colorGREY
    }*/
}
