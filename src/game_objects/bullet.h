#ifndef BULLET_H
#define BULLET_H


#include <QObject>


#include "movable.h"


class Bullet : public Movable {
    const int SIZE = CELL_SIZE / 2;     // 10
    const int STEP = CELL_SIZE / 10;     // 2

    bool user;

public:
    Bullet(QQuickItem* parent=nullptr);
    ~Bullet() override;

    int getSize(void) const override;
    int getStep(void) const override;

    void setDirection(Direction _direction) { direction = _direction; }

    bool isUsers(void) const { return user; }
    void setUser(bool _f) { user =_f; }

    void run(void);

    void onAllowed(void);

    void paint(QPainter *painter) override;
};




class BulletBehavior : public QObject {
    Q_OBJECT

    const int DURATION = 1;
    const int STEP = CELL_SIZE / 5;

    Q_PROPERTY(int step READ step)
    Q_PROPERTY(double speed READ speed)
    Q_PROPERTY(int duration READ duration NOTIFY durationChanged)

public:
    BulletBehavior() : QObject() {}
    ~BulletBehavior() override {}


    int step(void) const { return STEP; }
    double speed(void) const { return DURATION / STEP; }
    int duration(void) const { return DURATION; }

signals:
    void moveNorth(void);
    void moveEast(void);
    void moveSouth(void);
    void moveWest(void);

    void durationChanged(int _duration);
};



#endif // BULLET_H
