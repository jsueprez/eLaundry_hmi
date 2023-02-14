import QtQuick 2.5
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0
import "."

Item {
    id: frontendWelcome
    anchors.fill: parent

    onVisibleChanged: {
        if(!visible) return;

        animationWelcome.start();
    }

    Component.onCompleted: {
        backendWelcome.set_frontend(this)
        animationWelcome.start();
    }

    Rectangle {
        id: background

        anchors.fill: parent
        color: ELaundry.colorWHITE

        Image {
            id: novaLogo
            width: 387
            height: 84
            source: "images/novaLogo.png"
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    SequentialAnimation{
        id: animationWelcome
        running: false
        onStopped:
        {
            background.opacity = 0.0;
            backendWelcome.on_welcome_animation_end();
        }

        NumberAnimation {target: novaLogo; properties: "opacity"; from: 0.0; to: 1.0; duration: 400}
        PauseAnimation {duration: 4000}
        NumberAnimation {target: novaLogo; properties: "opacity"; from: 1.0; to: 0.0; duration: 600}
    }
}
