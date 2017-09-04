#ifndef FACTORIES_H
#define FACTORIES_H


#include <QString>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QDebug>

#include "../game_objects/bullet.h"
#include "../game_objects/enemy_tank.h"
#include "../game_objects/user_tank.h"
#include "../game_objects/user_base.h"


class BulletFactory {
    QString BULLET_PATH = "qrc:/qml/bullet.qml";
    QQmlComponent* component;
public:
    BulletFactory(QQmlEngine* _engine)  {
        component = new QQmlComponent(_engine, QUrl(BULLET_PATH));
    }

    ~BulletFactory() {
        delete component;
    }


    Bullet* makeBullet(Direction direction, int x, int y, int size) const {
        Bullet* bullet = nullptr;
        switch(direction) {
            case Direction::North:
                bullet = static_cast<Bullet*>(component->create());
                bullet->setX(x + (size / 2) - bullet->getSize() / 2);
                bullet->setY(y - bullet->getSize());
                break;
            case Direction::East:
                bullet = static_cast<Bullet*>(component->create());
                bullet->setX(x + size);
                bullet->setY(y + (size / 2) - (bullet->getSize() / 2));
                break;
            case Direction::South:
                bullet = static_cast<Bullet*>(component->create());
                bullet->setX(x + (size / 2) - (bullet->getSize() / 2));
                bullet->setY(y + size);
                break;
            case Direction::West:
                bullet = static_cast<Bullet*>(component->create());
                bullet->setX(x - bullet->getSize());
                bullet->setY(y + (size / 2) - (bullet->getSize() / 2));
                break;
        }
        if(bullet == nullptr)
            qDebug() << "not ok";

        bullet->setDirection(direction);
        return bullet;
    }
};



class EnemyFactory {
    QString ENEMY_PATH = "qrc:/qml/enemy_tank.qml";
    QQmlComponent* compoenent;

public:
    EnemyFactory(QQmlEngine* _engine) :
        compoenent(new QQmlComponent(_engine, QUrl(ENEMY_PATH))) {}

    ~EnemyFactory() {
        delete compoenent;
    }


    EnemyTank* makeEnemy(int x, int y) const {
        EnemyTank* tank = static_cast<EnemyTank*>(compoenent->create());
        tank->setX(x); tank->setY(y);
        tank->turnSouth();
        return tank;
    }
};



class UserFactory {
    QString USER_PATH = "qrc:/qml/user_tank.qml";
    QString BASE_PATH = "qrc:/qml/user_base.qml";

    QQmlComponent* component;
    QQmlComponent* base_comp;

public:
    UserFactory(QQmlEngine* _engine) {
        component = new QQmlComponent(_engine, QUrl(USER_PATH));
        base_comp = new QQmlComponent(_engine, QUrl(BASE_PATH));
    }

    ~UserFactory() {
        delete component;
        delete base_comp;
    }


    UserTank* makeUser(int x, int y) const {
        UserTank* tank = static_cast<UserTank*>(component->create());
        tank->setX(x); tank->setY(y);
        tank->turnNorth();
        return tank;
    }


    UserBase* makeBase(int x, int y) const {
        UserBase* base = static_cast<UserBase*>(base_comp->create());
        base->setX(x); base->setY(y);
        return base;
    }
};

#endif // FACTORIES_H
