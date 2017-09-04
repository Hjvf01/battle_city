#include "armor_wall.h"



ArmorWall::ArmorWall(QQuickItem *parent) : BaseGameObject(parent) {
    rect.setWidth(CELL_SIZE);
    rect.setHeight(CELL_SIZE);

    setWidth(CELL_SIZE);
    setHeight(CELL_SIZE);
}

ArmorWall::~ArmorWall() {}



void ArmorWall::paint(QPainter *painter) {
    painter->setBrush(QBrush(Qt::white));
    painter->drawRect(rect);
}
