/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gamecontroller.h"

#include <QGraphicsRectItem>
#include <QObject>

class Projectile: public QObject, public QGraphicsEllipseItem
{
Q_OBJECT
public:
    Projectile(int zValue, int modifier, bool &gameIsPaused, Weapon *w);

    void fly(bool outOfBounds);

private:
    Weapon *w_;

    int modifier_;

    bool &gameIsPaused_;
};

#endif // PROJECTILE_H
