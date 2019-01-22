#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <QGraphicsRectItem>
#include <QObject>

class Projectile: public QObject, public QGraphicsRectItem
{
Q_OBJECT
public:
    Projectile(int speed, int dmg);

    void fly(bool outOfBounds);

private:
    int speed_;
    int dmg_;
};

#endif // PROJECTILE_H
