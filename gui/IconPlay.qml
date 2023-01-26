import QtQuick 2.5
import QtQuick.Controls 2.0
import "."

Item{
    Canvas{
        id : playIcon
        anchors.fill: parent


        onPaint: {
            // Get drawing context
            var context = getContext("2d");

            //Draw a triangle
            context.beginPath();
            context.fillStyle = Wallbox.colorCHARGING
            context.strokeStyle = "black"
            context.moveTo(width *.30 ,height * .15);
            context.lineTo(width *.30 ,height * .85);
            context.lineTo(width *.75 ,height * .50);
            context.closePath();
            context.fill();
        }
    }
}



