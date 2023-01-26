import QtQuick 2.5
import QtQuick.Controls 2.0
//import QtGraphicalEffects 1.0
import "."

Item {
    id: itemHalo

    property var haloAngle : 0
    property color currentColor : Wallbox.colorStateWB_CURRENT

    onCurrentColorChanged: {
        innerHalo.requestPaint()
        outterHalo.requestPaint()
    }

    Behavior on currentColor
    {
        enabled: !appWindow.instant
        ColorAnimation {  duration: 200; }
    }

    /* The halo is formed by two circle called the innerHalo and the outterHalo.
    The innerHalo is rotating from 0 to 360 degrees ant the outterHalo is static */
    Canvas {
        id: outterHalo
        anchors.fill: parent

        onPaint: {
            // Get drawing context
            var context = getContext("2d");
            // Draw a circle
            context.beginPath();
            context.fillStyle = currentColor
            context.strokeStyle ="black"
            context.moveTo(width, height/2);
            context.arc((width/2) , height/2, 112, 0, 2* Math.PI, true)
            context.fill();
            context.stroke();
        }
    }

    Canvas {
        id: innerHalo
        anchors.fill: parent

        onPaint: {

            // Get drawing context
            var context = getContext("2d");
            // Draw a circle
            context.beginPath();
            context.fillStyle = "black"
            context.strokeStyle = "black"//currentColor
            context.moveTo((width + 6) -15, (height)/2);
            context.arc((width + 6)/2, (height)/2, 105, 0, 2* Math.PI, true)
            context.fill();
            context.stroke();
        }
    }

    IconLock {
        id: iconLock
        width: 150
        height: 150
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        opened: appWindow.stateDashboard !== iLaundry.stateDashboard_LOCK
        opacity: appWindow.stateDashboard !== iLaundry.stateDashboard_LOCK ? 0.0 : 1.0
    }

    IconPlay{

        onVisibleChanged: {
            if(!visible) return

            playAnimation.start()

        }

        id: iconPlay
        width: 100
        height: 100
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        opacity: 0.0
        visible: appWindow.stateDashboard === iLaundry.stateDashboard_PLAY

        SequentialAnimation{
            id: playAnimation
            running: false
            onRunningChanged:
                if(!running)
                {
                    backendDashboard.on_play_end()
                }
            NumberAnimation { target: iconPlay; properties: "opacity"; from: 0.0; to: 1.0; duration: 1000;  }
            PauseAnimation{duration: 1000}
            NumberAnimation { target: iconPlay; properties: "opacity"; from: 1.0; to: 0.0; duration: 1000;  }
        }
    }

    IconPause{

        onVisibleChanged: {
            if(!visible) return

            pauseAnimation.start()

        }

        id: iconPause
        width: 100
        height: 100
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        opacity: 0.0
        visible: appWindow.stateDashboard === iLaundry.stateDashboard_PAUSE

        SequentialAnimation{
            id: pauseAnimation
            running: false
            onRunningChanged:
                if(!running)
                {
                    backendDashboard.on_pause_end()
                }
            NumberAnimation { target: iconPause; properties: "opacity"; from: 0.0; to: 1.0; duration: 1000;  }
            PauseAnimation{duration: 2000}
            NumberAnimation { target: iconPause; properties: "opacity"; from: 1.0; to: 0.0; duration: 1000;  }

        }
    }

    Label{
        id: labelCurrent

        property bool visibility : false;
        anchors.centerIn:  parent
        anchors.verticalCenterOffset: 8
        color: Wallbox.colorStateWB_CURRENT
        font.capitalization: Font.AllUppercase
        wrapMode: Text.WordWrap
        opacity: parent.opacity
        text: frontendDashboard.userAmperes + " A"

        visible: (appWindow.stateDashboard === iLaundry.stateDashboard_CURRENT || labelCurrent.visibility);

        onTextChanged:
        {
            if(appWindow.stateDashboard === iLaundry.stateDashboard_POWER)
            {
                labelPower.visibility = false;
                labelCurrent.visibility= true;
                labelCurrentTimer.restart();
            }
        }

        Timer {
            id : labelCurrentTimer
            interval: 1500; running: false; repeat: false; triggeredOnStart: false
            onTriggered: {
                labelCurrent.visibility = false;
                labelPower.visibility = true;
            }
        }
    }

    Label{
        id: labelPower

        property bool visibility : true;
        anchors.centerIn:  parent
        anchors.verticalCenterOffset: 8
        color: iLaundry.colorCHARGING
        font.capitalization: Font.AllUppercase
        wrapMode: Text.WordWrap
        opacity: parent.opacity
        text: frontendDashboard.power + " kw"

        visible: (appWindow.stateDashboard === iLaundry.stateDashboard_POWER && labelPower.visibility);
    }

    ParallelAnimation {
        running: true
        loops: Animation.Infinite

        SequentialAnimation{
            RotationAnimation { target: innerHalo; properties: "rotation"; from:   0; to:  90; duration: 400; easing.type: Easing.Linear}
            RotationAnimation { target: innerHalo; properties: "rotation"; from:  90; to: 180; duration: 400; easing.type: Easing.Linear}
            RotationAnimation { target: innerHalo; properties: "rotation"; from: 180; to: 270; duration: 400; easing.type: Easing.Linear}
            RotationAnimation { target: innerHalo; properties: "rotation"; from: 270; to: 360; duration: 400; easing.type: Easing.Linear}
        }
    }
}

