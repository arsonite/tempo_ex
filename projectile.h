#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gamecontroller.h"

#include <QGraphicsRectItem>
#include <QObject>

class Projectile: public QObject, public QGraphicsEllipseItem
{
Q_OBJECT
public:
    Projectile(int zValue, Weapon *w, int modifier, GameController *g);

    void fly(bool outOfBounds);

private:
    Weapon *w_;

    GameController *g_;

    int modifier_;
};

#endif // PROJECTILE_H
