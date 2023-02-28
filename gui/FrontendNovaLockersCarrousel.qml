import QtQuick 2.5
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0
import "."

Item {
    id: frontendNovaLockersCarrousel
    anchors.fill: parent


    function updateLockStatus()
    {
        console.log("Send lock to :", pathView.currentItem.locked);
        backendDashboard.update_lock_state(pathView.currentItem.novaLockerId, pathView.currentItem.locked)
    }

    onVisibleChanged: {
        if (!visible) return
    }

    Rectangle {
        id: background

        anchors.fill: parent
        radius: 20
        color: ELaundry.colorWHITE_SMOKE
    }

    Component  {
        id : delegateCard

        Item {
            id: itemCard
            opacity: PathView.isCurrentItem ? 1 : 0.5
            width: 100
            height: 150

            property int novaLockerId: display.novaLockerId
            property string locked: display.line2

            z: PathView.z
            scale: PathView.scale
            Image {
                id: iconNovaLocker
                anchors.horizontalCenter: nameText.horizontalCenter
                width: 100; height: 100
                source: locked === "0" ? "images/laundry_not_available.png" : "images/laundry_available.png"
            }
            Text {
                id: nameText
                anchors.top: iconNovaLocker.bottom
                anchors.topMargin: 5
                text: novaLockerId
                font.pointSize: 14
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (pathView.currentIndex === model.index)
                    {
                        updateLockStatus()
                    }
                    else
                    {
                        pathView.currentIndex = model.index
                    }
                }
            }
        }
    }

    PathView {
        id: pathView
        anchors.fill: parent
        pathItemCount: 3
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        interactive: true
        model: backendDashboard.model
        delegate: delegateCard

        path: Path {
            startX: 60
            startY: pathView.height * 0.5

            PathPercent { value: 0.0 }
            PathAttribute { name: "z"; value: 4 }
            PathAttribute { name: "scale"; value: 0.6 }

            PathLine { x: pathView.width * 0.45; y: pathView.height * 0.5 }
            PathPercent { value: 0.45 }
            PathAttribute { name: "z"; value: 8 }
            PathAttribute { name: "scale"; value: 1.5 }

            PathLine { x: pathView.width * 0.75; y: pathView.height * 0.5 }
            PathPercent { value: 0.55 }
            PathAttribute { name: "z"; value: 8 }
            PathAttribute { name: "scale"; value: 1.5 }

            PathLine { x: pathView.width; y: pathView.height * 0.5 }
            PathPercent { value: 1.0 }
            PathAttribute { name: "z"; value: 4 }
            PathAttribute { name: "scale"; value: 0.6 }
        }
    }


}
