#ifndef BRICK_WALL_H
#define BRICK_WALL_H

#include "base.h"


class BrickWall : public BaseGameObject {
public:
    BrickWall(QQuickItem* parent=nullptr);
    ~BrickWall() override;

    void paint(QPainter *painter) override;
};

#endif // BRICK_WALL_H
