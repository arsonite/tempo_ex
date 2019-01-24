#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gamecontroller.h"

#include <QGraphicsRectItem>
#include <QObject>

class Projectile: public QObject, public QGraphicsRectItem
{
Q_OBJECT
public:
    Projectile(int zValue, int speed, int dmg, GameController *g);

    void fly(bool outOfBounds);

private:
    int speed_;
    int dmg_;

    GameController *g_;
};

#endif // PROJECTILE_H
