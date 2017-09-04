#include <ostream>
using std::ostream;
#include <unistd.h>
#include <cassert>

#include <QDebug>

#include "game_handler.h"




GameHandler::GameHandler(QQuickView* _view) : QObject() {
    view = _view;
    engine = view->engine();
    root = view->rootObject();

    board = new BoardController(view);

    user_factory = new UserFactory(engine);
    enemy_factory = new EnemyFactory(engine);

    finisher = root->findChild<GameFinisher*>("finisher");
    connect(
        board, &BoardController::enemyKill, this, &GameHandler::onEnemyKill
    );
    connect(
        board, &BoardController::userKill, this, &GameHandler::onUserKill
    );
    connect(
        board, &BoardController::baseDestroy, this, &GameHandler::onBaseDestroy
    );
}


GameHandler::~GameHandler() {
    delete board;
    delete user_factory;
    delete enemy_factory;

    delete engine;
    delete root;

    delete user;
    delete enemy_1;
    delete enemy_2;
}


void GameHandler::initUser() {
    UserTank* u_tank = user_factory->makeUser(
        USER_SPAWN.x() * CELL_SIZE, USER_SPAWN.y() * CELL_SIZE
    );
    user = new UserController(u_tank, view, board);
    board->setUser(user->getTank());
    UserBase* base = user_factory->makeBase(
        USER_BASE.x() * CELL_SIZE, USER_BASE.y() * CELL_SIZE
    );
    base->setParentItem(root);
    base->setParent(view);
    board->setBase(base);
}


void GameHandler::initEnemies() {
    EnemyTank* enemy_t = enemy_factory->makeEnemy(
        ENEMY_1.x() * CELL_SIZE, ENEMY_1.y() * CELL_SIZE
    );
    enemy_1 = new EnemyController(enemy_t, view, board);
    board->setEnemy1(enemy_1->getTank());
    enemies--;

    enemy_t = enemy_factory->makeEnemy(
        ENEMY_2.x() * CELL_SIZE, ENEMY_2.y() * CELL_SIZE
    );
    enemy_2 = new EnemyController(enemy_t, view, board);
    board->setEnemy2(enemy_2->getTank());
    enemies--;
}


void GameHandler::buildLevel() {
    board->initMap();
    board->buildLevel();
}


void GameHandler::onEnemyKill(EnemyTank *tank) {
    qDebug() << "enemy kill";

    enemies--;
        if(enemies == 0)
            win();

    if(tank == enemy_1->getTank()) {
        enemy_1->getTank()->setParentItem(nullptr);
        EnemyTank* enemy_t = enemy_factory->makeEnemy(
            ENEMY_1.x() * CELL_SIZE, ENEMY_1.y() * CELL_SIZE
        );
        enemy_1->changeTank(enemy_t);
        assert(enemy_1->getTank() == enemy_t);
        board->setEnemy1(enemy_t);


    } else {
        enemy_2->getTank()->setParentItem(nullptr);
        EnemyTank* enemy_t = enemy_factory->makeEnemy(
            ENEMY_2.x() * CELL_SIZE, ENEMY_2.y() * CELL_SIZE
        );
        enemy_2->changeTank(enemy_t);
        assert(enemy_2->getTank() == enemy_t);
        board->setEnemy2(enemy_t);
    }
}


void GameHandler::onUserKill() {
    qDebug() << "User kill";
    user->getTank()->setParentItem(nullptr);
    UserTank* tank = user_factory->makeUser(
        USER_SPAWN.x() * CELL_SIZE, USER_SPAWN.y() * CELL_SIZE
    );
    user->changeTank(tank);
    assert(user->getTank() == tank);
    board->setUser(tank);
    user_lives--;
    if(user_lives == 0)
        defeat();
}


void GameHandler::onBaseDestroy() {
    qDebug() << "Base destroy";
    defeat();
}


void GameHandler::win() {
    qDebug() << "win";
    finisher->win();
}


void GameHandler::defeat() {
    qDebug() << "defeat";
    finisher->defeat();
}
