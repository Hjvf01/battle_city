#include "bullet.h"


Bullet::Bullet(QQuickItem *parent) : Movable(parent) {
    rect.setWidth(SIZE);
    rect.setHeight(SIZE);

    setWidth(SIZE);
    setHeight(SIZE);
}

Bullet::~Bullet() {}


int Bullet::getSize(void) const { return SIZE; }
int Bullet::getStep(void) const { return STEP; }


void Bullet::paint(QPainter *painter) {
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(rect);
}
