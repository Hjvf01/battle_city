#include <iostream>
#include "user_tank.h"



UserTank::UserTank(QQuickItem *parent) : Movable(parent) {
    rect.setWidth(SIZE);
    rect.setHeight(SIZE);

    setWidth(SIZE);
    setHeight(SIZE);
}

UserTank::~UserTank() {}


void UserTank::decreaseLives() { --lives; }
void UserTank::increaseLives() { ++lives; }


int UserTank::getSize() const { return SIZE; }
int UserTank::getStep() const { return STEP; }


void UserTank::paint(QPainter *painter) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    painter->setBrush(QBrush(Qt::green));
    painter->drawRect(rect);
}
