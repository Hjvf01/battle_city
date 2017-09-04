#include <ostream>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

#include <QDebug>

#include "controllers.h"


std::ostream& operator <<(std::ostream& os, CellType type) {
    switch(type) {
        case CellType::Empty: return os << string(" ");
        case CellType::Brick: return os << string("B");
        default: return os << string("A");
    }
}



BoardController::BoardController(QQuickView *_view) : QObject() {
    view = _view;
    root = view->rootObject();

    builder = new Builder(":/levels/level_1.dat", view->engine());
}


BoardController::~BoardController() {
    delete builder;

    for(auto w: walls) delete w;
}



void BoardController::initMap() {
    map = builder->getMap();
}

void BoardController::buildLevel() {
    walls = builder->buildItems();

    for(QQuickItem* item: walls) {
        item->setParentItem(root);
        item->setParent(view);
    }
}


bool BoardController::canMoveEast(Movable *item) {
    int x = item->x();
    int y = item->y();
    int size = item->getSize();
    int step = item->getStep();

    CellType empty = CellType::Empty;

    int row = y / CELL_SIZE;
    int _row = (y + size - 1) / CELL_SIZE;
    int col = (x + size) / CELL_SIZE;
    if(col == 26) col = 25;

    Bullet* bullet = dynamic_cast<Bullet*>(item);
    if(bullet != nullptr)
        if(collideBullet(bullet))
            return false;

    if(map[row][col] != empty || map[_row][col] != empty)
        return false;

    return x + size + step <= FIELD_SIZE;
}


bool BoardController::canMoveNorth(Movable *item) {
    int y = item->y();
    int x = item->x();
    int size = item->getSize();
    int step = item->getStep();

    CellType empty = CellType::Empty;

    int row = (y - step) / CELL_SIZE;
    int col = x / CELL_SIZE;
    int _col = (x + size - 1) / CELL_SIZE;
    if(row == -1) row = 0;

    Bullet* bullet = dynamic_cast<Bullet*>(item);
    if(bullet != nullptr)
        if(collideBullet(bullet))
            return false;

    if(map[row][col] != empty || map[row][_col] != empty)
        return false;

    return y + step > step;
}


bool BoardController::canMoveSouth(Movable *item) {
    int y = item->y();
    int x = item->x();
    int size = item->getSize();
    int step = item->getStep();

    CellType empty = CellType::Empty;

    int row = (y + size) / CELL_SIZE;
    if(row > 25) row = 25;
    int col = x / CELL_SIZE;
    int _col = (x + size - 1) / CELL_SIZE;

    Bullet* bullet = dynamic_cast<Bullet*>(item);
    if(bullet != nullptr)
        if(collideBullet(bullet))
            return false;

    if(map[row][_col] != empty || map[row][col] != empty)
        return false;

    return y + size + step <= FIELD_SIZE;
}


bool BoardController::canMoveWest(Movable *item) {
    int x = item->x();
    int y = item->y();
    int step = item->getStep();

    CellType empty = CellType::Empty;

    int row = y / CELL_SIZE;
    int _row = (y + item->getSize() - 1) / CELL_SIZE;
    int col = (x - step) / CELL_SIZE;
    if(col == -1) col = 0;

    Bullet* bullet = dynamic_cast<Bullet*>(item);
    if(bullet != nullptr)
        if(collideBullet(bullet))
            return false;

    if(map[row][col] != empty || map[_row][col] != empty)
        return false;

    return x + step > step;
}


bool BoardController::collideBullet(Bullet *bullet) {
    QPoint point1(bullet->x(), bullet->y());
    QPoint point2(bullet->x() + 10, bullet->y() + 10);
    if(bullet->isUsers()) {
        QRect rect1(enemy1->x(), enemy1->y(), 40, 40);
        QRect rect2(enemy2->x(), enemy2->y(), 40, 40);
        if(rect1.contains(point1) || rect1.contains(point2)) {
            emit enemyKill(enemy1);
            return true;
        } else if(rect2.contains(point1) || rect2.contains(point2)) {
            emit enemyKill(enemy2);
            return true;
        }
    } else {
        QRect rect(user->x(), user->y(), 40, 40);
        QRect rect_b(base->x(), base->y(), 40, 40);
        if(rect.contains(point1) || rect.contains(point2)) {
            emit userKill();
            return true;
        } else if(rect_b.contains(point1) || rect.contains(point2)) {
            emit baseDestroy();
            return true;
        }
    }
    return false;
}


void BoardController::destroy(int x, int y, Direction direction) {
    switch(direction) {
        case Direction::East: return destroyFromEast(x, y);
        case Direction::North: return destroyFromNorth(x, y);
        case Direction::South: return destroyFromSouth(x, y);
        case Direction::West: return destroyFromWest(x, y);
    }
}


void BoardController::freeCell(int x, int y) {
    map[y / CELL_SIZE][x / CELL_SIZE] = CellType::Empty;
}


void BoardController::destroyFromEast(int x, int y) {
    int size = CELL_SIZE / 2;
    int step = CELL_SIZE / 5;
    QQuickItem* for_delete1 = nullptr;
    QQuickItem* for_delete2 = nullptr;

    int x1 = x + size + step * 2;
    int y1 = y;

    int x2 = x + size + step * 2;
    int y2 = y + size;

    for(QQuickItem* item: walls) {
        QRect item_rect(
            item->x(), item->y(),
            CELL_SIZE, CELL_SIZE
        );
        ArmorWall* wall = dynamic_cast<ArmorWall*>(item);
        if(wall == nullptr) {
            if(item_rect.contains(x1, y1)) {
                freeCell(item->x(), item->y());
                item->setParentItem(nullptr);
                for_delete1 = item;
            }
            if(item_rect.contains(x2, y2)) {
                freeCell(item->x(), item->y());
                item->setParentItem(nullptr);
                for_delete2 = item;
            }
        }
    }

    walls.removeOne(for_delete1);
    walls.removeOne(for_delete2);
}


void BoardController::destroyFromNorth(int x, int y) {
    int size = CELL_SIZE / 2;
    int step = CELL_SIZE / 10;
    QQuickItem* for_delete1 = nullptr;
    QQuickItem* for_delete2 = nullptr;

    int x1 = x;
    int y1 = y - step;

    int x2 = x + size;
    int y2 = y - step;

    for(QQuickItem* item: walls) {
        QRect rect(
            item->x(), item->y(),
            CELL_SIZE, CELL_SIZE
        );

        if(dynamic_cast<BrickWall*>(item) != nullptr) {
            if(rect.contains(x1, y1)) {
                freeCell(item->x(), item->y());
                item->setParentItem(nullptr);
                for_delete1 = item;
            }
            if(rect.contains(x2, y2)) {
                freeCell(item->x(), item->y());
                item->setParentItem(nullptr);
                for_delete2 = item;
            }
        }
    }

    walls.removeOne(for_delete1);
    walls.removeOne(for_delete2);
}


void BoardController::destroyFromSouth(int x, int y) {
    int size = CELL_SIZE / 2;
    int step = CELL_SIZE / 10;
    QQuickItem* for_delete1 = nullptr;
    QQuickItem* for_delete2 = nullptr;

    int x1 = x;
    int y1 = y + size + step;
    int x2 = x + size;
    int y2 = y + size + step;

    for(QQuickItem* item: walls) {
        QRect rect(
            item->x(), item->y(),
            CELL_SIZE, CELL_SIZE
        );

        if(dynamic_cast<BrickWall*>(item) != nullptr) {
            if(rect.contains(x1, y1)) {
                freeCell(item->x(), item->y());
                item->setParentItem(nullptr);
                for_delete1 = item;
            }
            if(rect.contains(x2, y2)) {
                freeCell(item->x(), item->y());
                item->setParentItem(nullptr);
                for_delete2 = item;
            }
        }
    }

    walls.removeOne(for_delete1);
    walls.removeOne(for_delete2);
}


void BoardController::destroyFromWest(int x, int y) {
    int size = CELL_SIZE / 2;
    int step = CELL_SIZE / 10;
    QQuickItem* for_delete1 = nullptr;
    QQuickItem* for_delete2 = nullptr;

    int x1 = x - step;
    int y1 = y;

    int x2 = x - step;
    int y2 = y + size;

    for(QQuickItem* item: walls) {
        QRect rect(
            item->x(), item->y(),
            CELL_SIZE, CELL_SIZE
        );

        if(dynamic_cast<BrickWall*>(item) != nullptr) {
            if(rect.contains(x1, y1)) {
                freeCell(item->x(), item->y());
                item->setParentItem(nullptr);
                for_delete1 = item;
            }
            if(rect.contains(x2, y2)) {
                freeCell(item->x(), item->y());
                item->setParentItem(nullptr);
                for_delete2 = item;
            }
        }
    }

    walls.removeOne(for_delete1);
    walls.removeOne(for_delete2);
}
