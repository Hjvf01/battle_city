#ifndef USER_BASE_H
#define USER_BASE_H


#include "base.h"


class UserBase : public BaseGameObject {
    static const int SIZE = CELL_SIZE * 2;

public:
    UserBase(QQuickItem* parent=nullptr);
    ~UserBase();

    void paint(QPainter *painter) override;
};


#endif // USER_BASE_H
