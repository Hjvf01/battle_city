#include "brick_wall.h"

BrickWall::BrickWall(QQuickItem *parent) : BaseGameObject(parent) {
    rect.setWidth(CELL_SIZE);
    rect.setHeight(CELL_SIZE);

    setWidth(CELL_SIZE);
    setHeight(CELL_SIZE);
}

BrickWall::~BrickWall() {}


void BrickWall::paint(QPainter *painter) {
    painter->setBrush(QBrush(QColor(255, 165, 0)));
    painter->drawRect(rect);
}
