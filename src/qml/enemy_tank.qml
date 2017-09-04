import QtQuick 2.5

import Tanks 1.0
import Behaviors 1.0


EnemyTank {
    id: tank

    signal finish(EnemyTank _tank);

    PropertyAnimation  {
        id: move2North
        target: tank
        properties: "y"
        to: 0
        duration: controller.duration
        alwaysRunToEnd: true

        onStopped: {
            finish(tank)
        }
    }


    PropertyAnimation {
        id: move2East
        target: tank
        properties: "x"
        to: 0
        duration: controller.duration
        alwaysRunToEnd: true

        onStopped: {
            finish(tank)
        }
    }

    PropertyAnimation {
        id: move2South
        target: tank
        properties: "y"
        to: 0
        duration: controller.duration;
        alwaysRunToEnd: true

        onStopped: {
            finish(tank);
        }
    }

    PropertyAnimation {
        id: move2West
        target: tank
        properties: "x"
        to: 0
        duration: controller.duration
        alwaysRunToEnd: true

        onStopped: {
            finish(tank);
        }
    }


    EnemyBehavior {
        id: controller
        objectName: "enemy_controller"

        onMoveEast: {
            move2East.to = tank.x + controller.step
            move2East.restart()
        }

        onMoveNorth: {
            move2North.to = tank.y - controller.step
            move2North.restart()
        }

        onMoveSouth: {
            move2South.to = tank.y + controller.step
            move2South.restart()
        }

        onMoveWest: {
            move2West.to = tank.x - controller.step
            move2West.restart()
        }

        onShoot: {
            console.log("shoot")
        }
    }
}
