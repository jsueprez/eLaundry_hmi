import QtQuick 2.5
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0
import "."

Item {
    id: frontendNovaLockersCarrousel
    anchors.fill: parent

    function updateLockStatus()
    {
        backendDashboard.update_lock_state(pathView.currentItem.novaLockerId, pathView.currentItem.locked)
    }

    onVisibleChanged: {
        if (!visible) return

        appWindow.mainAreaX = Qt.binding(function() { return background.x })
        appWindow.mainAreaW = Qt.binding(function() { return background.width })

    }

    Rectangle {
        id: background

        anchors.fill: parent
        color: ELaundry.colorWHITE_SMOKE
    }

    Component  {
        id : delegateCard

        Item {
            id: itemCard
            height: 240
            width: 240

            visible: PathView.onPath
            z: PathView.itemZ
            scale: PathView.itemScale
            antialiasing: true

            property color color: PathView.isCurrentItem ? ELaundry.colorCYAN : ELaundry.colorCONNECTED
            property int novaLockerId: display.novaLockerId
            property string locked: display.line2

            Behavior on color { ColorAnimation { duration: 250 } }

            Image {
                id: iconNovaLocker
                anchors.horizontalCenter: itemCard.horizontalCenter
                width: 200; height: 200
                source: locked === "0" ? "images/laundry_not_available.png" : "images/laundry_available.png"

            }
            Text {
                id: nameText
                anchors.top: iconNovaLocker.bottom
                anchors.topMargin: 5
                anchors.horizontalCenter: iconNovaLocker.horizontalCenter
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
        model: backendDashboard.model
        delegate: delegateCard

        path: Path {
            startX: 0
            startY: pathView.height * 0.5

            PathAttribute { name: "itemZ"; value: 0 }
            PathAttribute { name: "itemAngle"; value: -90.0; }
            PathAttribute { name: "itemScale"; value: 0.5; }
            PathLine { x: frontendNovaLockersCarrousel.width * 0.4; y: frontendNovaLockersCarrousel.height / 2; }
            PathPercent { value: 0.48; }
            PathLine { x: frontendNovaLockersCarrousel.width * 0.5; y: frontendNovaLockersCarrousel.height / 2; }
            PathAttribute { name: "itemAngle"; value: 0.0; }
            PathAttribute { name: "itemScale"; value: 1.0; }
            PathAttribute { name: "itemZ"; value: 100 }
            PathLine { x: frontendNovaLockersCarrousel.width * 0.6; y: frontendNovaLockersCarrousel.height / 2; }
            PathPercent { value: 0.52; }
            PathLine { x: frontendNovaLockersCarrousel.width; y: frontendNovaLockersCarrousel.height / 2; }
            PathAttribute { name: "itemAngle"; value: 90.0; }
            PathAttribute { name: "itemScale"; value: 0.5; }
            PathAttribute { name: "itemZ"; value: 0 }
        }

        pathItemCount:5
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        interactive: true
    }
}
