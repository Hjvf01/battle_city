#ifndef CONTROLLERS_H
#define CONTROLLERS_H


#include <stdlib.h>
#include <time.h>

#include <QObject>
#include <QQuickView>

#include "../builders/builder.h"
#include "../builders/factories.h"

#include "../game_objects/movable.h"
#include "../game_objects/user_tank.h"
#include "../game_objects/enemy_tank.h"
#include "../game_objects/bullet.h"
#include "../game_objects/brick_wall.h"
#include "../game_objects/armor_wall.h"




static const int FILED_SIZE = CELL_SIZE * 26;




class BoardController : public QObject {
    Q_OBJECT

    QList<QList<CellType>> map;
    QList<QQuickItem*> walls;
    Builder* builder;

    QQuickView* view;
    QQuickItem* root;

    UserTank* user;
    EnemyTank* enemy1 = nullptr;
    EnemyTank* enemy2 = nullptr;
    UserBase* base = nullptr;

signals:
    void enemyKill(EnemyTank*);
    void userKill();
    void baseDestroy();

public:
    BoardController(QQuickView* _view);
    ~BoardController() override;

    void initMap(void);
    void buildLevel(void);

    bool canMoveNorth(Movable* item);
    bool canMoveEast(Movable* item);
    bool canMoveSouth(Movable* item);
    bool canMoveWest(Movable* item);

    void setEnemy1(EnemyTank* tank) { enemy1 = tank; }
    void setEnemy2(EnemyTank* tank) { enemy2 = tank; }
    void setBase(UserBase* _base) { base = _base; }
    void setUser(UserTank* tank) { user = tank; }

    void destroy(int x, int y, Direction direction);

private:
    void destroyFromEast(int, int);
    void destroyFromNorth(int, int);
    void destroyFromSouth(int, int);
    void destroyFromWest(int, int);

    void freeCell(int row, int col);

    bool collideBullet(Bullet* bullet);
};




class BulletController : public QObject {
    Q_OBJECT

    BoardController* board;
    BulletBehavior* behavior;
    Bullet* bullet;

    QQuickView* view;
    QQuickItem* root;
    bool users;

public:
    BulletController(
        Bullet* _bullet,
        BoardController* _board,
        QQuickView* _view,
        bool _users = false
     );

    ~BulletController();

    Bullet* getBullet(void) const { return bullet; }

    void run();

public slots:
    void onStopped(QQuickPaintedItem*);

signals:
    void explode(BulletController* _this);

private:
    void moveForvard();
    void initBullet();

    bool canMoveNorth();
    bool canMoveEast();
    bool canMoveSouth();
    bool canMoveWest();
};




class EnemyController : public QObject {
    Q_OBJECT

    EnemyTank* tank;
    QQuickView* view;
    QQuickItem* root;
    BoardController* board;
    EnemyBehavior* behavior;
    BulletFactory* bullets_factory;
    QList<BulletController*> bullets;

    QList<Direction> all_except_north = {
        Direction::West, Direction::East, Direction::West
    };
    QList<Direction> all_except_east = {
        Direction::North, Direction::South, Direction::South
    };
    QList<Direction> all_except_south = {
        Direction::East, Direction::East, Direction::West
    };
    QList<Direction> all_except_west = {
        Direction::North, Direction::South, Direction::East
    };

public:
    EnemyController(
        EnemyTank* _tank,
        QQuickView* _view,
        BoardController* _board
    );
    ~EnemyController();

    void changeTank(EnemyTank* _tank);

    EnemyTank* getTank(void) const { return tank; }

    void run();

public slots:
    void onStopped(QQuickPaintedItem* item);
    void onExplode(BulletController* bullet);

private:
    void chooseDirection(void);
    void shoot(void);
    void initTank(void);
};




class UserController : public QObject {
    Q_OBJECT

    UserTank* tank;
    QQuickView* view;
    QQuickItem* root;
    BoardController* board;
    BulletFactory* bullets_factory;
    QList<BulletController*> bullets;

public:
    UserController(
        UserTank* _tank,
        QQuickView* _view,
        BoardController* _board
    );

    ~UserController() override;

    void changeTank(UserTank* _tank);
    UserTank* getTank(void) const { return tank; }

public slots:
    void onMoveNorth();
    void onMoveEast();
    void onMoveSouth();
    void onMoveWest();

    void onShoot();

    void onExplode(BulletController* bullet);

private:
    void initTank(void);
};

#endif // CONTROLLERS_H
