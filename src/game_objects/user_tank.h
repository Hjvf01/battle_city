#ifndef USER_TANK_H
#define USER_TANK_H


#include "movable.h"


class UserTank : public Movable {
    static const int SIZE = CELL_SIZE * 2;
    static const int STEP = CELL_SIZE / 10;

    Direction direction;
    int lives = 3;

public:
    UserTank(QQuickItem* parent=nullptr);
    ~UserTank() override;

    int getSize(void) const override;
    int getStep(void) const override;

    void decreaseLives(void);
    void increaseLives(void);

    void paint(QPainter *painter) override;
};


#endif // USER_TANK_H
