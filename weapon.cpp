/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#include "weapon.h"

#include <QBrush>
#include <QPen>

Weapon::Weapon(QGraphicsRectItem *parent, int c, int x, int y): c_(c), x_(x), y_(y)
{
    switch(c) {
        case 1:
            dmg_ = 20;
            speed_.setX(0);
            speed_.setY(15);
            reloadTime_ = 250;
            break;
        case 2:
            dmg_ = 30;
            speed_.setX(-10);
            speed_.setY(10);
            reloadTime_ = 500;
            break;
        case 3:
            dmg_ = 40;
            speed_.setX(0);
            speed_.setY(25);
            reloadTime_ = 1000;
            break;
    }

    width_ = 5;
    height_ = 20;
    setRect(x/2-width_/2, y, width_, height_);
    setBrush(QBrush(QColor(250, 250, 250)));
    setPen(QPen(Qt::NoPen));
    setParentItem(parent);
}

void Weapon::setSpeed(QPoint speed)
{
    speed_ = speed;
}

QPoint Weapon::getSpeed()
{
    return speed_;
}

int Weapon::getClass()
{
    return c_;
}

int Weapon::getDamage()
{
    return dmg_;
}

int Weapon::getReloadTime()
{
    return reloadTime_;
}
