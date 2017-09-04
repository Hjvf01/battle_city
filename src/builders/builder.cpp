#include <cassert>

#include <QtCore/QDebug>

#include "builder.h"



Builder::Builder(const QString &name, QQmlEngine* _engine) {
    engine = _engine;
    QFile level(name);
    if(level.open(QIODevice::ReadOnly)) {
        content = level.readAll().split('\n');
        level.close();
    }

    buildMap();
}

Builder::~Builder() {}



void Builder::buildMap(void) {
    int height = content.size();
    for(int row = 0; row < height; row++) {
        int width = content[row].size();
        map.push_back(QList<CellType>{});
        for(int col = 0; col < width; col++) {
            if(content[row][col] == ALPHABET[0]) {
                map[row].push_back(CellType::Empty);
            } else if(content[row][col] == ALPHABET[1]) {
                map[row].push_back(CellType::Brick);
            } else if(content[row][col] == ALPHABET[2]) {
                map[row].push_back(CellType::Armor);
            }
        }
    }

    assert(map.size() == content.size());
    assert(map[3].size() == content[3].size());
}


QList<QQuickItem*> Builder::buildItems() const {
    QList<QQuickItem*> result;

    int height = map.size();
    for(int row = 0; row < height; row++) {
        int width = map[row].size();
        for(int col = 0; col < width; col++) {
            QQuickItem* item = nullptr;

            if(map[row][col] == CellType::Empty)
                continue;
            else if(map[row][col] == CellType::Brick) {
                QQmlComponent component(engine, QUrl(BRICK_URL));
                item = static_cast<QQuickItem*>(component.create());
            } else if(map[row][col] == CellType::Armor) {
                QQmlComponent component(engine, QUrl(ARMOR_URL));
                item = static_cast<QQuickItem*>(component.create());
            }

            item->setX(CELL_SIZE * col);
            item->setY(CELL_SIZE * row);
            result.append(item);
        }
    }

    return result;
}


QList<QList<CellType>> Builder::getMap() const { return map; }
