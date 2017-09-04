#include "controllers.h"




UserController::UserController(
    UserTank *_tank,
    QQuickView *_view,
    BoardController *_board
) : QObject() {
    tank = _tank;
    view = _view;
    board = _board;
    root = view->rootObject();
    bullets_factory = new BulletFactory(view->engine());

    initTank();
}


UserController::~UserController() {
    delete tank;
    delete bullets_factory;

    for(auto bullet: bullets) delete bullet;
}


void UserController::changeTank(UserTank *_tank) {
    tank = _tank;
    initTank();
}


void UserController::initTank() {
    tank->setParentItem(root);
    tank->setParent(view);

    connect(
        tank, SIGNAL(moveNorth()),
        this, SLOT(onMoveNorth())
    );
    connect(
        tank, SIGNAL(moveEast()),
        this, SLOT(onMoveEast())
    );
    connect(
        tank, SIGNAL(moveSouth()),
        this, SLOT(onMoveSouth())
    );
    connect(
        tank, SIGNAL(moveWest()),
        this, SLOT(onMoveWest())
    );
    connect(
        tank, SIGNAL(shoot()),
        this, SLOT(onShoot())
    );
}


void UserController::onMoveEast() {
    if(tank->getDirection() != Direction::East)
        return tank->turnEast();

    if(board->canMoveEast(tank))
        tank->setX(tank->x() + tank->getStep());
}


void UserController::onMoveNorth() {
    if(tank->getDirection() != Direction::North)
        return tank->turnNorth();

    if(board->canMoveNorth(tank))
        tank->setY(tank->y() - tank->getStep());
}


void UserController::onMoveSouth() {
    if(tank->getDirection() != Direction::South)
        return tank->turnSouth();

    if(board->canMoveSouth(tank))
        tank->setY(tank->y() + tank->getStep());
}


void UserController::onMoveWest() {
    if(tank->getDirection() != Direction::West)
        return tank->turnWest();

    if(board->canMoveWest(tank))
        tank->setX(tank->x() - tank->getStep());
}


void UserController::onShoot() {
    BulletController* b_contr = new BulletController(
        bullets_factory->makeBullet(
            tank->getDirection(),
            tank->x(),
            tank->y(),
            tank->getSize()
        ),
        board,
        view,
        true
    );
    bullets.append(b_contr);
    connect(
        b_contr, &BulletController::explode,
        this, &UserController::onExplode
    );
}


void UserController::onExplode(BulletController *bullet) {
    Bullet* _bullet = bullet->getBullet();
    board->destroy(_bullet->x(), _bullet->y(), _bullet->getDirection());
    bullets.removeOne(bullet);
    delete bullet;
}
