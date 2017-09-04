#ifndef MOVABLE_H
#define MOVABLE_H


#include <ostream>

#include "base.h"

enum class Direction {
    North = 0,
    East = 1,
    South = 2,
    West = 3
};




class Movable : public BaseGameObject {
protected:
    Direction direction;

public:
    Movable(QQuickItem* parent=nullptr) :
        BaseGameObject(parent), direction(Direction::North) {}

    virtual ~Movable() override {}

    Direction getDirection(void) const { return direction; }
    void setDirection(Direction _direction) { direction = _direction; }

    virtual int getSize(void) const = 0;
    virtual int getStep(void) const = 0;

    void turnNorth(void) { direction = Direction::North; }
    void turnEast(void) { direction = Direction::East; }
    void turnSouth(void) { direction = Direction::South; }
    void turnWest(void) { direction = Direction::West; }
};


#endif // MOVABLE_H
