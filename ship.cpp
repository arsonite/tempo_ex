#include <ship.h>

#include <QBrush>
#include <QPen>

Ship::Ship(int c, QGraphicsRectItem *parent): c_(c), health_(2+c)
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

    setPen(QPen(Qt::NoPen));
    setRect(0, 0, hitboxX_, hitboxY_);
    setPos(0, 0);

    setParentItem(parent);
}

void Ship::constructBasic()
{
    hitboxX_ = 50;
    hitboxY_ = 100;

    weapons_.push_back(new Weapon(this, 1, hitboxX_, 0));

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
    int r2W = 25;
    int r2H = 50;
    r2->setRect(hitboxX_/2-r2W/2, 30, r2W, r2H);
    r2->setBrush(QBrush(QColor(60, 80, 100)));
    r2->setPen(QPen(Qt::NoPen));

    QGraphicsRectItem *r3 = new QGraphicsRectItem(this);
    int r3W = 5;
    int r3H = 50;
    r3->setRect(hitboxX_/2-r3W/2, 30, r3W, r3H);
    r3->setBrush(QBrush(QColor(200, 200, 255)));
    r3->setPen(QPen(Qt::NoPen));

    QGraphicsPolygonItem *leftFlap = new QGraphicsPolygonItem(this);
    QPolygonF leftFlapTriangle;
    leftFlapTriangle.append(QPoint(0, 0));
    leftFlapTriangle.append(QPoint(-25, 35));
    leftFlapTriangle.append(QPoint(0, 35));
    leftFlap->setPolygon(leftFlapTriangle);
    leftFlap->setBrush(QBrush(QColor(45, 90, 180)));
    leftFlap->setPen(QPen(Qt::NoPen));
    leftFlap->setPos(hitboxX_/2-1.8, 65);

    QGraphicsPolygonItem *rightFlap = new QGraphicsPolygonItem(this);
    QPolygonF rightFlapTriangle;
    rightFlapTriangle.append(QPoint(0, 0));
    rightFlapTriangle.append(QPoint(25, 35));
    rightFlapTriangle.append(QPoint(0, 35));
    rightFlap->setPolygon(rightFlapTriangle);
    rightFlap->setBrush(QBrush(QColor(45, 90, 180)));
    rightFlap->setPen(QPen(Qt::NoPen));
    rightFlap->setPos(hitboxX_/2+2.8, 65);
}

void Ship::constructFighter()
{
    hitboxX_ = 125;
    hitboxY_ = 125;
}

void Ship::constructCruiser()
{
    hitboxX_ = 150;
    hitboxY_ = 150;
}

void Ship::constructDreadnought()
{
    hitboxX_ = 175;
    hitboxY_ = 175;
}

QPoint Ship::getHitbox()
{
    return QPoint(hitboxX_, hitboxY_);
}

std::vector<Weapon*> Ship::getWeapons()
{
    return weapons_;
}

int Ship::getClass()
{
    return c_;
}

int Ship::getHealth()
{
    return health_;
}
