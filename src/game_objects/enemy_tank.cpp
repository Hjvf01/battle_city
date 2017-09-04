#include "enemy_tank.h"


EnemyTank::EnemyTank(QQuickItem *parent) : Movable(parent) {
    rect.setWidth(SIZE);
    rect.setHeight(SIZE);

    setWidth(SIZE);
    setHeight(SIZE);

    direction = Direction::North;
}

EnemyTank::~EnemyTank() {}


int EnemyTank::getSize() const { return SIZE; }
int EnemyTank::getStep() const { return STEP; }


void EnemyTank::paint(QPainter *painter) {
    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(rect);
}
