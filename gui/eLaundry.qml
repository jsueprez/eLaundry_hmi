pragma Singleton

import QtQuick 2.5

QtObject {

    property color colorStateWB_CURRENT: colorREADY

    readonly property string fontDefault: "Calibre"

    readonly property color colorREADY: "#00ad91"
    readonly property color colorCONNECTED: "#78a7c5"
    readonly property color colorCHARGING: "#3434da"
    readonly property color colorERROR: "#e89274"
    readonly property color colorLOCKED: "#be9e01"
    readonly property color colorBLACK: "#000000"

    readonly property color colorCYAN: "#249dd6"
    readonly property color colorGREY_LIGHT: "#c4c4c4"
    readonly property color colorGREY: "#60726d"
    readonly property color colorGREY_DARK: "#444444"
    readonly property color colorRED: "#b8524d"
    readonly property color colorWALLBOX: "#4dc1a1"
    readonly property color colorWHITE: "#ffffff"

    readonly property int connectionETH: 0
    readonly property int connectionWIFI: 1
    readonly property int connectionGSM: 2
    readonly property int connectionNONE: 3

    readonly property int profileAdmin: 2
    readonly property int profileUser: 1

    readonly property int stateUI_IDLE               : -1
    readonly property int stateUI_WELCOME_ANIMATION  : 0
    readonly property int stateUI_WELCOME_MESSAGE    : 1
    readonly property int stateUI_DASHBOARD          : 2
    readonly property int stateUI_FACE_RECOGNITION   : 3
    readonly property int stateUI_BRANDING           : 4

    readonly property int stateDashboard_CURRENT     : 0
    readonly property int stateDashboard_POWER       : 1
    readonly property int stateDashboard_LOCK        : 2
    readonly property int stateDashboard_PLAY        : 3
    readonly property int stateDashboard_PAUSE       : 4
    readonly property int stateDashboard_IDLE        : 5

    readonly property int stateWB_READY        : 0xA1
    readonly property int stateWB_PS_UNCONFIG  : 0xA2
    readonly property int stateWB_CONNECTED1   : 0xB1
    readonly property int stateWB_CONNECTED2   : 0xB2
    readonly property int stateWB_CONNECTED3   : 0xB3
    readonly property int stateWB_CONNECTED4   : 0xB4
    readonly property int stateWB_CONNECTED5   : 0xB5
    readonly property int stateWB_CONNECTED6   : 0xB6
    readonly property int stateWB_WAIT_CURRENT1: 0xB7
    readonly property int stateWB_WAIT_CURRENT2: 0xB8
    readonly property int stateWB_WAIT_CURRENT3: 0xB9
    readonly property int stateWB_WAIT_CURRENT4: 0xBA
    readonly property int stateWB_CHARGING1    : 0xC1
    readonly property int stateWB_CHARGING2    : 0xC2
    readonly property int stateWB_ERROR        : 0x0E
    readonly property int stateWB_UNVIABLE     : 0x0F
    readonly property int stateWB_LOCK         : 0xD1
    readonly property int stateWB_WAIT_UNLOCK  : 0xD2

}
