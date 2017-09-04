#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H


#include <QtCore/QObject>
#include <QtQuick/QQuickView>
#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickItem>


#include "controllers.h"
#include "../builders/factories.h"


static const QPoint USER_SPAWN(12, 13);
static const QPoint USER_BASE(12, 24);
static const QPoint ENEMY_1(0, 0);
static const QPoint ENEMY_2(24, 0);



class GameFinisher : public QObject {
    Q_OBJECT

public:
    GameFinisher() : QObject() {}
    ~GameFinisher() {}

signals:
    void win();
    void defeat();
};



class GameHandler : public QObject {
    Q_OBJECT

    QQmlEngine* engine;
    QQuickItem* root;
    QQuickView* view;
    BoardController* board;

    UserController* user;
    UserFactory* user_factory;

    EnemyController* enemy_1;
    EnemyController* enemy_2;
    EnemyFactory* enemy_factory;
    int user_lives = 3;
    int enemies = 20;

    GameFinisher* finisher = nullptr;

public:
    GameHandler(QQuickView* _view);
    ~GameHandler() override;

    void initUser(void);
    void initEnemies(void);
    void buildLevel(void);

private slots:
    void onEnemyKill(EnemyTank* tank);
    void onUserKill();
    void onBaseDestroy();

private:
    void defeat();
    void win();
};


#endif // GAME_HANDLER_H
