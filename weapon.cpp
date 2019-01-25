#include "weapon.h"

#include <QBrush>
#include <QPen>

Weapon::Weapon(QGraphicsRectItem *parent, int c, int x, int y): c_(c), x_(x), y_(y)
{
    switch(c) {
        case 1:
            equipLaser();
            break;
        case 2:
            equipCannon();
            break;
        case 3:
            equipRockets();
            break;
    }

    width_ = 5;
    height_ = 20;
    setRect(x/2-width_/2, y, width_, height_);
    setBrush(QBrush(QColor(250, 250, 250)));
    setPen(QPen(Qt::NoPen));
    setParentItem(parent);
}

void Weapon::equipLaser()
{

}

void Weapon::equipCannon()
{

}

void Weapon::equipRockets()
{

}
