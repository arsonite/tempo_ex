#ifndef SHIP_H
#define SHIP_H

#include <weapon.h>

#include <vector>

#include <QGraphicsRectItem>

class Ship: public QGraphicsRectItem
{
public:
    Ship(int c, QGraphicsRectItem *parent);

    QPoint getHitbox();

    std::vector<Weapon*> getWeapons();

private:
    void constructBasic();
    void constructFighter();
    void constructCruiser();
    void constructDreadnought();

    int hitboxX_;
    int hitboxY_;

    std::vector<Weapon*> weapons_;
};

#endif // SHIP_H
