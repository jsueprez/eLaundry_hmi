import QtQuick 2.5
import QtQuick.Controls 2.0
import QtGraphicalEffects 1.0
import "."

Item {
    id: frontendNovaLockersCarrousel
    anchors.fill: parent


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
        id : delegate
        Column {
            id: wrapper
            opacity: PathView.isCurrentItem ? 1 : 0.5
            z: PathView.z
            scale: PathView.scale
            Image {
                anchors.horizontalCenter: nameText.horizontalCenter
                width: 100; height: 100
                source: icon
            }
            Text {
                id: nameText
                text: name
                font.pointSize: 16
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
        model: NovaLockerModel {}
        delegate: delegate

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
