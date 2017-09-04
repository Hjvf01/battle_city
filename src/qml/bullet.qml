import QtQuick 2.5

import Behaviors 1.0
import Bullets 1.0


Bullet {
id: bullet

    signal finish(Bullet bullet)

    BulletBehavior {
        id: bullet_controller
        objectName: "controller"

        onMoveEast: {
            move2East.to = bullet.x + bullet_controller.step
            move2East.restart()
        }

        onMoveNorth: {
            move2North.to = bullet.y - bullet_controller.step
            move2North.restart()
        }

        onMoveSouth: {
            move2South.to = bullet.y + bullet_controller.step
            move2South.restart()
        }

        onMoveWest: {
            move2West.to = bullet.x - bullet_controller.step
            move2West.restart();
        }
    }

    PropertyAnimation {
        id: move2North
        target: bullet
        properties: "y"
        to: 0
        duration: bullet_controller.duration
        alwaysRunToEnd: true

        onStopped: {
            finish(bullet);
        }
    }

    PropertyAnimation {
        id: move2East
        target: bullet
        properties: "x"
        to: 0
        duration: bullet_controller.duration
        alwaysRunToEnd: true

        onStopped: {
            finish(bullet)
        }
    }

    PropertyAnimation {
        id: move2South
        target: bullet
        properties: "y"
        to: 0
        duration: bullet_controller.duration
        alwaysRunToEnd: true

        onStopped: {
            finish(bullet)
        }
    }

    PropertyAnimation {
        id: move2West
        target: bullet
        properties: "x"
        to: 0
        duration: bullet_controller.duration
        alwaysRunToEnd: true

        onStopped: {
            finish(bullet)
        }
    }
}
