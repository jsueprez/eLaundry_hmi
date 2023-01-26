import QtQuick 2.5
import QtQuick.Controls 2.0
import "."

ApplicationWindow {
    id: appWindow

    property int stateUI: iLaundry.stateUI_IDLE
    property int stateWB: iLaundry.stateWB_READY
    property int stateDashboard: iLaundry.stateDashboard_CURRENT

    property string userName : "iLaundry"

    property int animationTimeoutWelcomeMessage : 1000;

    property bool onBoot : true
    property bool onBootWelcomeMessage : true

    /* Connection type and signal strength */
    property int connType: iLaundry.connectionNONE
    property int connStrength: 4

    /* Whether the user can lock or not */
    property bool lockable: true

    /* Workaround fix for the flattened screen issue */
    property real xScale: 1.0

    /* Connection status icons */
    property bool iconMyiLaundry: false
    property bool iconBluetooth: false
    property bool iconScheduled: false
    property bool iconPowerBoost: false
    property bool iconFaceRecognition: false

    /* Whether the halo Item is showm or not */
    property bool itemHalo: false

    /* Whether the play Item is showm or not */
    property bool showPlay: false

    /* Whether the pause Item is showm or not */
    property bool showPause: false

    /* Whether the face Item is show or not, this property is set to true when the thread of FaceRecognition start*/
    property bool unlockingCamera: false

    /* Whether the animation for faceRecognition is running or not, this property is set to true when the FaceRecognition process completely ends*/
    property bool faceRecognitionEnd : true

    /* Used when it is needed to change the color of the halo without do the color animation */
    property bool instant : false

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
    width: 480
    height: 272
    title: "iLaundry"
    color: "black"
    font.family: iLaundry.fontDefault
    font.pointSize: 50

    Component.onCompleted: {
        /* First element to show */
        //frontendWelcome.visible = true
    }

    onStateUIChanged: {
        console.log("STATE changed UI to:"+ stateUI);

        if (stateUI === iLaundry.stateUI_DASHBOARD)
        {
            updateWBState(stateWB);
        }
        else if (stateUI === iLaundry.stateUI_FACE_RECOGNITION)
        {
            iconFaceRecognition = true;
        }
        else if (stateUI === iLaundry.stateUI_BRANDING)
        {
            updateWBState(stateWB);
        }
        else if (stateUI === iLaundry.stateUI_WELCOME_MESSAGE)
        {
            updateWBState(stateWB);
        }
    }

    onStateDashboardChanged:  {
        console.log("STATE changed UIDashboard to:"+ stateDashboard);

        if (stateDashboard === iLaundry.stateDashboard_IDLE)
        {
            instant = true
            iLaundry.colorStateWB_CURRENT = iLaundry.colorBLACK
        }
        else if (stateDashboard === iLaundry.stateDashboard_CURRENT)
        {
            instant = false
            updateWBState(stateWB);
        }
        else if (stateDashboard === iLaundry.stateDashboard_POWER)
        {
            instant = false
            updateWBState(stateWB);
        }
        else if (stateDashboard === iLaundry.stateDashboard_LOCK)
        {
            instant = true
            iLaundry.colorStateWB_CURRENT = iLaundry.colorLOCKED
        }

    }

    /* Refresh screen if needed */
    onStateWBChanged: {
        updateWBState(stateWB);
    }

    function updateWBState(stateWB)
    {
        console.log("STATE changed WB to:"+ stateWB);
        if ((stateWB >= iLaundry.stateWB_CONNECTED1) && (stateWB <= iLaundry.stateWB_WAIT_CURRENT4))
        {
            iLaundry.colorStateWB_CURRENT = iLaundry.colorCONNECTED
        }
        else if (((stateWB === iLaundry.stateWB_CHARGING1) || (stateWB === iLaundry.stateWB_CHARGING2)))
        {
            iLaundry.colorStateWB_CURRENT = iLaundry.colorCHARGING
        }
        else if ((stateWB === iLaundry.stateWB_ERROR) || (stateWB === iLaundry.stateWB_UNVIABLE) || (stateWB === iLaundry.stateWB_PS_UNCONFIG))
        {
            iLaundry.colorStateWB_CURRENT = iLaundry.colorERROR
        }
        else if ((stateWB === iLaundry.stateWB_READY))
        {
            iLaundry.colorStateWB_CURRENT = iLaundry.colorREADY
        }

    }

    /* This item is the main window where most of the state of the charger take place, it also show the current state of connections */
//    FrontendDashboard {
//        id: frontendDashboard
//        visible: stateUI === iLaundry.stateUI_DASHBOARD
//        objectName: "frontendDashboard"
//        x :125
//        z:  0

//    }

//    /* This item is used for showing the branding if it is necessary */
//    FrontendStandby {
//        id: frontendStandby
//        visible: stateUI === iLaundry.stateUI_BRANDING
//        objectName: "frontendStandby"
//        z: 4
//    }

//    /* This item is used for showing the iLaundry animation when the charger is booting */
//    FrontendWelcome {
//        id: frontendWelcome
//        visible: stateUI === iLaundry.stateUI_WELCOME_ANIMATION
//        objectName: "frontendWelcome"
//        z: 5
//    }

}
