#ifndef SHIP_H
#define SHIP_H

#include <QGraphicsRectItem>

class Ship: public QGraphicsRectItem
{
public:
    Ship(int c, QGraphicsRectItem *parent);

    QPoint getHitbox();

private:
    void constructBasic();
    void constructFighter();
    void constructCruiser();
    void constructDreadnought();

    int hitboxX_;
    int hitboxY_;
};

#endif // SHIP_H
