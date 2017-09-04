#ifndef BULLET_LOG_H
#define BULLET_LOG_H


#include <QObject>


class Bullet;


class BulletLog : QObject {
    Q_OBJECT

public:
    BulletLog() : QObject() {}

signals:
    void moveForward(Bullet*);
};


#endif // BULLET_LOG_H
