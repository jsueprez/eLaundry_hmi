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
            height: 290
            width: 240
            z: PathView.z
            scale: PathView.scale

            property color color: PathView.isCurrentItem ? ELaundry.colorCYAN : ELaundry.colorCONNECTED
            property int novaLockerId: display.novaLockerId
            property string locked: display.line2

            Behavior on color { ColorAnimation { duration: 250 } }

            Image {
                id: iconNovaLocker
                anchors.horizontalCenter: nameText.horizontalCenter
                width: 200; height: 200
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
        pathItemCount: 5
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        interactive: true
        model: backendDashboard.model
        delegate: delegateCard

        path: Path {
            startX: 0
            startY: pathView.height * 0.5

            PathPercent { value: 0.0 }
            PathAttribute { name: "z"; value: 4 }
            PathAttribute { name: "scale"; value: 0.8 }

            PathLine { x: pathView.width * 0.35; y: pathView.height * 0.5 }
            PathPercent { value: 0.45 }
            PathAttribute { name: "z"; value: 8 }
            PathAttribute { name: "scale"; value: 1.0 }

            PathLine { x: pathView.width * 0.65; y: pathView.height * 0.5 }
            PathPercent { value: 0.55 }
            PathAttribute { name: "z"; value: 8 }
            PathAttribute { name: "scale"; value: 1.0 }

            PathLine { x: pathView.width; y: pathView.height * 0.5 }
            PathPercent { value: 1.0 }
            PathAttribute { name: "z"; value: 4 }
            PathAttribute { name: "scale"; value: 0.8 }
        }
    }


}
