#ifndef ARMOR_WALL_H
#define ARMOR_WALL_H


#include "base.h"


class ArmorWall : public BaseGameObject {
public:
    ArmorWall(QQuickItem* parent=nullptr);
    ~ArmorWall() override;

    void paint(QPainter* painter) override;
};


#endif // ARMOR_WALL_H
