#include <cassert>

#include "controllers.h"



BulletController::BulletController(
    Bullet* _bullet,
    BoardController* _board,
    QQuickView* _view,
    bool _users
) : QObject() {
    board = _board;
    bullet = _bullet;
    view = _view;
    users = _users;
    bullet->setUser(users);

    initBullet();
}

BulletController::~BulletController() {
    bullet->setParentItem(nullptr);
}



void BulletController::run() { return moveForvard(); }


void BulletController::initBullet() {
    behavior = bullet->findChild<BulletBehavior*>("controller");

    bullet->setParentItem(view->rootObject());
    bullet->setParent(view);

    connect(
        bullet, SIGNAL(finish(QQuickPaintedItem*)),
        this, SLOT(onStopped(QQuickPaintedItem*))
    );

    run();
}


void BulletController::onStopped(QQuickPaintedItem *item) {
    assert(dynamic_cast<Bullet*>(item) == bullet);
    return moveForvard();
}


void BulletController::moveForvard() {
    switch(bullet->getDirection()) {
        case Direction::North:
            if(board->canMoveNorth(bullet)) {
                emit behavior->moveNorth();
                return;
            } else {
                emit explode(this);
                return;
            }
        case Direction::East:
            if(board->canMoveEast(bullet)) {
                emit behavior->moveEast();
                return;
            } else {
                emit explode(this);
                return;
            }
        case Direction::South:
            if(board->canMoveSouth(bullet)) {
                emit behavior->moveSouth();
                return;
            } else {
                emit explode(this);
                return;
            }
        case Direction::West:
            if(board->canMoveWest(bullet)) {
                emit behavior->moveWest();
                return;
            } else {
                emit explode(this);
                return;
            }
        }
}
