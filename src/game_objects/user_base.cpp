#include "user_base.h"



UserBase::UserBase(QQuickItem *parent) : BaseGameObject(parent) {
    rect.setWidth(SIZE);
    rect.setHeight(SIZE);

    setWidth(SIZE);
    setHeight(SIZE);
}


UserBase::~UserBase() {}


void UserBase::paint(QPainter *painter) {
    painter->setBrush(Qt::darkGray);
    painter->drawRect(rect);
}
