#include "ship.h"

#include <QBrush>
#include <QPen>

Ship::Ship(int c)
{
    switch(c) {
        case 1:
            constructBasic();
            break;
        case 2:
            constructFighter();
            break;
        case 3:
            constructCruiser();
            break;
        case 4:
            constructDreadnought();
            break;
    }


    QPoint s1P((900-hitboxX_)/2, (700-hitboxY_)/2);
    setPen(QPen(QColor(255, 0, 0)));
    setRect(0, 0, hitboxX_, hitboxY_);
    setPos(s1P);
}

void Ship::constructBasic()
{
    hitboxX_ = 100;
    hitboxY_ = 100;

    QGraphicsRectItem *r1 = new QGraphicsRectItem(this);
    int r1W = 25;
    int r1H = 65;
    r1->setRect(hitboxX_/2-r1W/2, 25, r1W, r1H);
    r1->setBrush(QBrush(QColor(45, 135, 255)));
    r1->setPen(QPen(Qt::NoPen));

    QGraphicsEllipseItem *e1 = new QGraphicsEllipseItem(this);
    int e1S = 25;
    e1->setRect(hitboxX_/2-r1W/2, r1W/2, e1S, e1S);
    e1->setBrush(QBrush(QColor(45, 135, 255)));
    e1->setPen(QPen(Qt::NoPen));

    QGraphicsRectItem *r2 = new QGraphicsRectItem(this);
    int r2W = 10;
    int r2H = 50;
    r2->setRect(hitboxX_/2-r2W, 25, r2W, r2H);
    r2->setBrush(QBrush(QColor(250, 250, 250)));
    r2->setPen(QPen(Qt::NoPen));
}

void Ship::constructFighter()
{

}

void Ship::constructCruiser()
{

}

void Ship::constructDreadnought()
{

}

QPoint Ship::getHitbox()
{
    return QPoint(hitboxX_, hitboxY_);
}

