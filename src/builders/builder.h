#ifndef BUILDER_H
#define BUILDER_H


#include <QtCore/QList>
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtQuick/QQuickItem>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>

#include "../game_objects/base.h"


enum class CellType {
    Empty = 0,
    Brick,
    Armor
};


static const int FIELD_SIZE = CELL_SIZE * 26;

static const QString BRICK_URL = "qrc:/qml/brick_wall.qml";
static const QString ARMOR_URL = "qrc:/qml/armor_wall.qml";


class Builder {
    QQmlEngine* engine;
    QList<QList<CellType>> map;
    QList<QByteArray> content;

    const QList<char> ALPHABET = {
        'S', // Empty
        'W', // Brick wall
        'A'  // Armor wall
    };

public:
    Builder(const QString& name, QQmlEngine* _engine);
    ~Builder();

    QList<QQuickItem*> buildItems(void) const;
    QList<QList<CellType>> getMap(void) const;

private:
    void buildMap(void);
};


#endif // BUILDER_H
