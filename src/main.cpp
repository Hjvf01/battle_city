#include <QGuiApplication>
#include <QtQuick/QQuickView>

#include "controllers/game_handler.h"
#include "game_objects/armor_wall.h"
#include "game_objects/brick_wall.h"
#include "game_objects/user_base.h"


int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    qmlRegisterType<UserTank>("Tanks", 1, 0, "UserTank");
    qmlRegisterType<EnemyTank>("Tanks", 1, 0, "EnemyTank");
    qmlRegisterType<EnemyBehavior>("Behaviors", 1, 0, "EnemyBehavior");

    qmlRegisterType<BrickWall>("Walls", 1, 0, "BrickWall");
    qmlRegisterType<ArmorWall>("Walls", 1, 0, "ArmorWall");

    qmlRegisterType<UserBase>("UBase", 1, 0, "Base");
    qmlRegisterType<Bullet>("Bullets", 1, 0, "Bullet");
    qmlRegisterType<BulletBehavior>("Behaviors", 1, 0, "BulletBehavior");

    qmlRegisterType<GameFinisher>("Game", 1, 0, "GameFin");


    QQuickView view;
    view.setSource(QUrl("qrc:/qml/main.qml"));
    view.setTitle("Battle City QML");

    GameHandler handler(&view);
    handler.buildLevel();
    handler.initUser();
    handler.initEnemies();

    view.show();
    int res = app.exec();

    return res;
}
