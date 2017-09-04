import QtQuick 2.7
import QtQuick.Controls 2.1


import Game 1.0

Item {
    id: rootItem
    visible: true
    width: 700
    height: 520

    Rectangle {
        id: rect
        visible: true
        width: 520
        height: 520
        color: "black"
        x: 0
        y: 0

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log(mouse.x, mouse.y);
            }
        }
    }

    Rectangle {
        id: table
        x: 520
        y: 0
        width: 180
        height: 520
        color: "grey"

        TextArea {
            x: 540
            y: 30
            width: 100
            height: 50
            text: "30"
            font.pointSize: 15
        }
    }

    Popup {
        id: win
        x: 50
        y: 50
        width: 300
        height: 300
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        TextArea {
            anchors.fill: parent
            text: "You Win";
            font.pointSize: 30
            verticalAlignment: Text.AlignVCenter
        }
    }

    Popup {
        id: defeat
        x: 50
        y: 50
        width: 300
        height: 300
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

        TextArea {
            anchors.fill: parent
            text: "defeat"
            font.pointSize: 30
            verticalAlignment: Text.AlignVCenter
        }
    }

    GameFin {
        objectName: "finisher"

        onWin: {
            win.open()
        }

        onDefeat: {
            defeat.open()
        }
    }
}
