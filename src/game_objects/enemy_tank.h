#ifndef ENEMY_TANK_H
#define ENEMY_TANK_H


#include "movable.h"


class EnemyBehavior : public QObject {
    Q_OBJECT

    const int DURATION = 250;
    const int STEP = CELL_SIZE;

    Q_PROPERTY(int step READ step)
    Q_PROPERTY(double speed READ speed)
    Q_PROPERTY(int duration READ duration NOTIFY durationChanged)

public:
    EnemyBehavior() : QObject() {}
    ~EnemyBehavior() {}


    int step(void) const { return STEP; }
    double speed(void) const { return DURATION / STEP; }
    int duration(void) const { return DURATION; }

signals:
    void moveNorth(void);
    void moveEast(void);
    void moveSouth(void);
    void moveWest(void);

    void shoot(void);

    void durationChanged(int duration);
};




class EnemyTank : public Movable {
    static const int SIZE = CELL_SIZE * 2;
    static const int STEP = CELL_SIZE / 10;

    Direction direction;

public:
    EnemyTank(QQuickItem* parent=nullptr);
    ~EnemyTank() override;

    int getSize(void) const override;
    int getStep(void) const override;

    void paint(QPainter *painter) override;
};


#endif // ENEMY_TANK_H
