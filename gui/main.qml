import QtQuick 2.5
import QtQuick.Controls 2.0
import "."

ApplicationWindow {
    id: appWindow

    property int stateUI: ELaundry.stateUI_DASHBOARD
    property int stateWB: ELaundry.stateWB_READY
    property int stateDashboard: ELaundry.stateDashboard_CURRENT

    // used for resizing and positioning UI controls
    property int mainAreaX: 0
    property int mainAreaW: width

    // connection type and signal strength
    property int connType: ELaundry.connectionNONE
    property int connStrength: 4

    property string userName : "ELaundry"

    /* Workaround fix for the flattened screen issue */
    property real xScale: 1.0

    function applyMode(result)
    {
        switch (result)
        {
        case 1: // default user
        case 2: // single-user
            lockable = true
            break

        case 3: // multi-user
            lockable = true
            break

        case 4: // guest
            lockable = false
            break
        }
    }

    visible: true
    width: 800
    height: 480
    title: "ELaundry"
    color: "black"
    font.family: ELaundry.fontDefault
    font.pointSize: 50

    Component.onCompleted: {
        /* First element to show */
        //frontendWelcome.visible = true

        frontendDashboard.visible = true
    }

    onStateUIChanged: {
        console.log("STATE changed UI to:"+ stateUI);

        if (stateUI === ELaundry.stateUI_DASHBOARD)
        {
            updateWBState(stateWB);
        }
        else if (stateUI === ELaundry.stateUI_FACE_RECOGNITION)
        {
            iconFaceRecognition = true;
        }
        else if (stateUI === ELaundry.stateUI_BRANDING)
        {
            updateWBState(stateWB);
        }
        else if (stateUI === ELaundry.stateUI_WELCOME_MESSAGE)
        {
            updateWBState(stateWB);
        }
    }

    onStateDashboardChanged:  {
        console.log("STATE changed UIDashboard to:"+ stateDashboard);

        if (stateDashboard === ELaundry.stateDashboard_IDLE)
        {
            instant = true
            ELaundry.colorStateWB_CURRENT = ELaundry.colorBLACK
        }
        else if (stateDashboard === ELaundry.stateDashboard_CURRENT)
        {
            instant = false
            updateWBState(stateWB);
        }
        else if (stateDashboard === ELaundry.stateDashboard_POWER)
        {
            instant = false
            updateWBState(stateWB);
        }
        else if (stateDashboard === ELaundry.stateDashboard_LOCK)
        {
            instant = true
            ELaundry.colorStateWB_CURRENT = ELaundry.colorLOCKED
        }

    }

    /* Refresh screen if needed */
    onStateWBChanged: {
        updateWBState(stateWB);
    }

    function updateWBState(stateWB)
    {
        console.log("STATE changed WB to:"+ stateWB);
        if ((stateWB >= ELaundry.stateWB_CONNECTED1) && (stateWB <= ELaundry.stateWB_WAIT_CURRENT4))
        {
            ELaundry.colorStateWB_CURRENT = ELaundry.colorCONNECTED
        }
        else if (((stateWB === ELaundry.stateWB_CHARGING1) || (stateWB === ELaundry.stateWB_CHARGING2)))
        {
            ELaundry.colorStateWB_CURRENT = ELaundry.colorCHARGING
        }
        else if ((stateWB === ELaundry.stateWB_ERROR) || (stateWB === ELaundry.stateWB_UNVIABLE) || (stateWB === ELaundry.stateWB_PS_UNCONFIG))
        {
            ELaundry.colorStateWB_CURRENT = ELaundry.colorERROR
        }
        else if ((stateWB === ELaundry.stateWB_READY))
        {
            ELaundry.colorStateWB_CURRENT = ELaundry.colorREADY
        }

    }

    FrontendDashboard {
        id: frontendDashboard
        visible: stateUI === ELaundry.stateUI_DASHBOARD
        objectName: "frontendDashboard"
        z:  0
    }

    FrontendControlsUI {
        id: frontendControlsUI
        visible: true
    }

    FrontendWelcome {
        id: frontendWelcome
        visible: stateUI === ELaundry.stateUI_WELCOME_MESSAGE
        objectName: "frontendWelcome"
        z: 1
    }

}
