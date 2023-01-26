import QtQuick 2.5
import QtQuick.Controls 2.0
import "."

Item{
    Canvas{
        id : pauseIcon
        anchors.fill: parent

        property color foregroundPauseColor : Wallbox.colorCONNECTED

        onPaint: {
            // Get drawing context
            var context = getContext("2d");

            //Draw a rectangle 1
            context.beginPath();
            context.fillStyle = foregroundPauseColor
            context.fillRect(width * .25, height * .15, width * .18 , height * .75)
            context.strokeRect();

            //Draw a rectangle 2
            context.beginPath();
            context.fillStyle = foregroundPauseColor
            context.fillRect(width * .58, height * .15, width * .18 , height * .75)
            context.strokeRect();
        }
    }
}



