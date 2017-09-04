import QtQuick 2.0

import Tanks 1.0


UserTank {
    id: userTank


    signal moveNorth()
    signal moveEast()
    signal moveSouth()
    signal moveWest()

    signal shoot()


    Item {
        id: keyboard
        anchors.fill: parent
        focus: true
        Keys.onPressed: {
            if(event.key === Qt.Key_A) {
                  moveWest()
            } else if (event.key === Qt.Key_W) {
                moveNorth()
            } else if (event.key === Qt.Key_S) {
                moveSouth()
            } else if(event.key === Qt.Key_D) {
                moveEast()
            } else if(event.key === Qt.Key_Space) {
                shoot()
            }
        }
    }
}
