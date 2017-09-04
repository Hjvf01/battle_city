#ifndef BASE_H
#define BASE_H


#include <iostream>
using std::cout;
using std::endl;


#include <QtGui/QPainter>
#include <QtCore/QString>
#include <QtCore/QRect>
#include <QtQuick/QQuickPaintedItem>
#include <QtQuick/QQuickItem>




static const QString BASE_IMAGE_URL = "qrc:/images";
static const int CELL_SIZE = 20;




class BaseGameObject : public QQuickPaintedItem {
public:
    BaseGameObject(QQuickItem* parent=nullptr) : QQuickPaintedItem(parent) {}

    virtual ~BaseGameObject() override {}

protected:
    QRect rect;
};


#endif // BASE_H
