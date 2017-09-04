#include <cassert>

#include "controllers.h"



EnemyController::EnemyController(
    EnemyTank *_tank,
    QQuickView *_view,
    BoardController *_board
) : QObject() {
    tank = _tank;
    view = _view;
    board = _board;
    bullets_factory = new BulletFactory(view->engine());

    srand(time(NULL));

    initTank();
}


EnemyController::~EnemyController() {
    delete tank;
    delete bullets_factory;
}


void EnemyController::run() {
    return chooseDirection();
}


void EnemyController::changeTank(EnemyTank *_tank) {
    delete tank;

    tank = _tank;
    initTank();
}


void EnemyController::initTank() {
    behavior = tank->findChild<EnemyBehavior*>("enemy_controller");

    connect(
        tank, SIGNAL(finish(QQuickPaintedItem*)),
        this, SLOT(onStopped(QQuickPaintedItem*))
    );

    tank->setParentItem(view->rootObject());
    tank->setParent(view);

    run();
}


void EnemyController::onStopped(QQuickPaintedItem *item) {
    assert(dynamic_cast<EnemyTank*>(item) == tank);

    int num = rand() % 5 + 1;
    if(num == 2 || num == 3 || num == 4)
        shoot();
    else
        if(
            tank->getDirection() == Direction::South ||
            tank->getDirection() == Direction::North
          )
            tank->setDirection(Direction::West);
        else
            tank->setDirection(Direction::South);

    return chooseDirection();
}


void EnemyController::chooseDirection() {
    #define RANDOM_DIRECTION rand() % 2 + 0

    switch(tank->getDirection()) {
        case Direction::East:
            if(board->canMoveEast(tank)) {
                emit behavior->moveEast();
                return;
            } else {
                tank->setDirection(all_except_east[RANDOM_DIRECTION]);
                return run();
            }
        case Direction::North:
            if(board->canMoveNorth(tank)) {
                emit behavior->moveNorth();
                return;
            } else {
                tank->setDirection(all_except_north[RANDOM_DIRECTION]);
                return run();
            }
        case Direction::South:
            if(board->canMoveSouth(tank)) {
                emit behavior->moveSouth();
                return;
            } else {
                tank->setDirection(all_except_south[RANDOM_DIRECTION]);
                return run();
            }
        case Direction::West:
            if(board->canMoveWest(tank)) {
                emit behavior->moveWest();
                return;
            } else {
                tank->setDirection(all_except_west[RANDOM_DIRECTION]);
                return run();
            }
    }

    #undef RANDOM_DIRECTION
}


void EnemyController::shoot() {
    BulletController* b_contr = new BulletController(
        bullets_factory->makeBullet(
            tank->getDirection(),
            tank->x(),
            tank->y(),
            tank->getSize()
        ),
        board,
        view,
        false
    );
    bullets.append(b_contr);
    connect(
        b_contr, &BulletController::explode,
        this, &EnemyController::onExplode
    );
}


void EnemyController::onExplode(BulletController *bullet) {
    Bullet* _bullet = bullet->getBullet();
    board->destroy(_bullet->x(), _bullet->y(), _bullet->getDirection());
    bullets.removeOne(bullet);
    delete bullet;
}
