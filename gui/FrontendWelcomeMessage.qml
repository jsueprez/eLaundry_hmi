import QtQuick 2.5
import QtQuick.Controls 2.0
import "."

Item {
    id: frontendStandbyMessage
    width: parent.width
    height: 192

    onVisibleChanged: {
        if (!visible) return

        background.opacity = 1.0

    }

    /* Fucntion used for start the branding animation if it is needed */
    function startAnimation()
    {
        animationWelcomeMessage.running = true;
    }

    Component.onCompleted: {
        backendWelcomeMessage.set_frontend(this)
    }

    Rectangle {
        id: background

        anchors.fill: parent
        color: ELaundry.colorBLACK

        Label{
            id: lableWelcomeName
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: ELaundry.colorREADY
            wrapMode: Text.WordWrap
            opacity: 0.0
            text: "Welcome,\n" + appWindow.userName;//.split(" ")[0]+ " " + appWindow.userName.split(" ")[1]
            visible: opacity > 0.01 ? 1 : 0
        }
    }

    SequentialAnimation{
        id: animationWelcomeMessage
        running: false
        onStopped:
        {
            lableWelcomeName.opacity = 0.0;
            backendWelcomeMessage.on_welcome_message_end();
        }

        NumberAnimation {target: lableWelcomeName; properties: "opacity"; from: 0.0; to: 1.0; duration: 400}
        PauseAnimation {duration: 4000}
        NumberAnimation {target: lableWelcomeName; properties: "opacity"; from: 1.0; to: 0.0; duration: 400}
    }


}
