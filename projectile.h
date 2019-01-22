#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsRectItem>
#include <QObject>

class Projectile: public QObject, public QGraphicsRectItem
{
Q_OBJECT
public:
    Projectile();

    void fly(bool outOfBounds);
};

#endif // PROJECTILE_H
