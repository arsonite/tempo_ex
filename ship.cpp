/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#include <ship.h>

#include <QBrush>
#include <QPen>

Ship::Ship(int c, int weaponC, QGraphicsRectItem *parent) : c_(c), weaponC_(weaponC), health_(c * 2)
{
    switch (c)
    {
    case 1:
        constructRocket();
        break;
    case 2:
        constructFighter();
        break;
    case 3:
        constructCruiser();
        break;
    }
    setPen(QPen(Qt::NoPen));
    setRect(0, 0, hitboxX_, hitboxY_);
    setPos(0, 0);
    setParentItem(parent);
}

void Ship::constructRocket()
{
    hitboxX_ = 50;
    hitboxY_ = 100;

    speed_ = 12;

    weapons_.push_back(new Weapon(this, weaponC_, hitboxX_, 0));

    QGraphicsRectItem *r1 = new QGraphicsRectItem(this);
    int r1W = 25;
    int r1H = 65;
    r1->setRect(hitboxX_ / 2 - r1W / 2, 25, r1W, r1H);
    r1->setBrush(QBrush(QColor(45, 135, 255)));
    r1->setPen(QPen(Qt::NoPen));

    QGraphicsEllipseItem *e1 = new QGraphicsEllipseItem(this);
    int e1S = 25;
    e1->setRect(hitboxX_ / 2 - r1W / 2, r1W / 2, e1S, e1S);
    e1->setBrush(QBrush(QColor(45, 135, 255)));
    e1->setPen(QPen(Qt::NoPen));

    QGraphicsRectItem *r2 = new QGraphicsRectItem(this);
    int r2W = 25;
    int r2H = 50;
    r2->setRect(hitboxX_ / 2 - r2W / 2, 30, r2W, r2H);
    r2->setBrush(QBrush(QColor(60, 80, 100)));
    r2->setPen(QPen(Qt::NoPen));

    QGraphicsRectItem *r3 = new QGraphicsRectItem(this);
    int r3W = 5;
    int r3H = 50;
    r3->setRect(hitboxX_ / 2 - r3W / 2, 30, r3W, r3H);
    r3->setBrush(QBrush(QColor(200, 200, 255)));
    r3->setPen(QPen(Qt::NoPen));

    QPolygonF leftFlapTriangle;
    leftFlapTriangle.append(QPoint(0, 0));
    leftFlapTriangle.append(QPoint(-25, 35));
    leftFlapTriangle.append(QPoint(0, 35));
    QGraphicsPolygonItem *leftFlap = new QGraphicsPolygonItem(this);
    leftFlap->setPolygon(leftFlapTriangle);
    leftFlap->setBrush(QBrush(QColor(45, 90, 180)));
    leftFlap->setPen(QPen(Qt::NoPen));
    leftFlap->setPos(hitboxX_ / 2 - 1.8, 65);

    QPolygonF rightFlapTriangle;
    rightFlapTriangle.append(QPoint(0, 0));
    rightFlapTriangle.append(QPoint(25, 35));
    rightFlapTriangle.append(QPoint(0, 35));
    QGraphicsPolygonItem *rightFlap = new QGraphicsPolygonItem(this);
    rightFlap->setPolygon(rightFlapTriangle);
    rightFlap->setBrush(QBrush(QColor(45, 90, 180)));
    rightFlap->setPen(QPen(Qt::NoPen));
    rightFlap->setPos(hitboxX_ / 2 + 2.8, 65);
}

void Ship::constructFighter()
{
    hitboxX_ = 125;
    hitboxY_ = 100;

    speed_ = 10;

    weapons_.push_back(new Weapon(this, weaponC_, hitboxX_ / 2, 35));
    weapons_.push_back(new Weapon(this, weaponC_, hitboxX_ + hitboxX_ / 2, 35));

    QPolygonF leftFlapTriangle;
    leftFlapTriangle.append(QPoint(0, 10));
    leftFlapTriangle.append(QPoint(-hitboxX_ / 2, 100));
    leftFlapTriangle.append(QPoint(0, 80));
    QGraphicsPolygonItem *leftFlap = new QGraphicsPolygonItem(this);
    leftFlap->setPolygon(leftFlapTriangle);
    leftFlap->setBrush(QBrush(QColor(170, 0, 10)));
    leftFlap->setPen(QPen(Qt::NoPen));
    leftFlap->setPos(hitboxX_ / 2 - 1.8, 0);

    QPolygonF rightFlapTriangle;
    rightFlapTriangle.append(QPoint(0, 10));
    rightFlapTriangle.append(QPoint(hitboxX_ / 2, 100));
    rightFlapTriangle.append(QPoint(0, 80));
    QGraphicsPolygonItem *rightFlap = new QGraphicsPolygonItem(this);
    rightFlap->setPolygon(rightFlapTriangle);
    rightFlap->setBrush(QBrush(QColor(170, 0, 10)));
    rightFlap->setPen(QPen(Qt::NoPen));
    rightFlap->setPos(hitboxX_ / 2 + 2.8, 0);

    QGraphicsRectItem *r1 = new QGraphicsRectItem(this);
    int r1W = 5;
    int r1H = 80;
    r1->setRect(hitboxX_ / 2 - r1W / 2, 0, r1W, r1H);
    r1->setBrush(QBrush(QColor(225, 0, 10)));
    r1->setPen(QPen(Qt::NoPen));

    QPolygonF leftBodyTriangle;
    leftBodyTriangle.append(QPoint(0, 0));
    leftBodyTriangle.append(QPoint(-25, 100));
    leftBodyTriangle.append(QPoint(0, 80));
    QGraphicsPolygonItem *leftBody = new QGraphicsPolygonItem(this);
    leftBody->setPolygon(leftBodyTriangle);
    leftBody->setBrush(QBrush(QColor(200, 10, 10)));
    leftBody->setPen(QPen(Qt::NoPen));
    leftBody->setPos(hitboxX_ / 2 - 1.8, 0);

    QPolygonF rightBodyTriangle;
    rightBodyTriangle.append(QPoint(0, 0));
    rightBodyTriangle.append(QPoint(25, 100));
    rightBodyTriangle.append(QPoint(0, 80));
    QGraphicsPolygonItem *rightBody = new QGraphicsPolygonItem(this);
    rightBody->setPolygon(rightBodyTriangle);
    rightBody->setBrush(QBrush(QColor(200, 10, 10)));
    rightBody->setPen(QPen(Qt::NoPen));
    rightBody->setPos(hitboxX_ / 2 + 2.8, 0);

    QGraphicsEllipseItem *cockpit = new QGraphicsEllipseItem(this);
    int eW = 15;
    int eH = 25;
    cockpit->setRect(hitboxX_ / 2 - eW / 2, hitboxY_ - eH * 2 - eH / 2, eW, eH);
    cockpit->setBrush(QBrush(QColor(120, 200, 230)));
    cockpit->setPen(QPen(Qt::NoPen));
}

void Ship::constructCruiser()
{
    setPen(QPen(QColor(255, 0, 0)));

    hitboxX_ = 125;
    hitboxY_ = 150;

    speed_ = 8;

    weapons_.push_back(new Weapon(this, weaponC_, hitboxX_ - (5 / 2), 0));
    weapons_.push_back(new Weapon(this, weaponC_, hitboxX_ / 2 - 10, 60));
    weapons_.push_back(new Weapon(this, weaponC_, hitboxX_ + hitboxX_ / 2 + 10, 60));

    QPolygonF thrusterRectangle;
    thrusterRectangle.append(QPoint(-15, 50));
    thrusterRectangle.append(QPoint(-5, 150));
    thrusterRectangle.append(QPoint(8, 150));
    thrusterRectangle.append(QPoint(20, 50));
    QGraphicsPolygonItem *thruster = new QGraphicsPolygonItem(this);
    thruster->setPolygon(thrusterRectangle);
    thruster->setBrush(QBrush(QColor(50, 50, 50)));
    thruster->setPen(QPen(Qt::NoPen));
    thruster->setPos(hitboxX_ / 2 - 1.8, 0);

    QGraphicsRectItem *r1 = new QGraphicsRectItem(this);
    int r1W = 10;
    int r1H = 100;
    r1->setRect(hitboxX_ / 2 - r1W / 2, 15, r1W, r1H);
    r1->setBrush(QBrush(QColor(225, 225, 225)));
    r1->setPen(QPen(Qt::NoPen));

    QPolygonF leftWingTipTriangle;
    leftWingTipTriangle.append(QPoint(-50, 50));
    leftWingTipTriangle.append(QPoint(-60, 100));
    leftWingTipTriangle.append(QPoint(-3, 130));
    QGraphicsPolygonItem *leftWingTip = new QGraphicsPolygonItem(this);
    leftWingTip->setPolygon(leftWingTipTriangle);
    leftWingTip->setBrush(QBrush(QColor(125, 125, 125)));
    leftWingTip->setPen(QPen(Qt::NoPen));
    leftWingTip->setPos(hitboxX_ / 2 - 1.8, 0);

    QPolygonF leftWingTriangle;
    leftWingTriangle.append(QPoint(-3, 50));
    leftWingTriangle.append(QPoint(-60, 100));
    leftWingTriangle.append(QPoint(-3, 130));
    QGraphicsPolygonItem *leftWing = new QGraphicsPolygonItem(this);
    leftWing->setPolygon(leftWingTriangle);
    leftWing->setBrush(QBrush(QColor(155, 155, 155)));
    leftWing->setPen(QPen(Qt::NoPen));
    leftWing->setPos(hitboxX_ / 2 - 1.8, 0);

    QPolygonF rightWingTipTriangle;
    rightWingTipTriangle.append(QPoint(+55, 50));
    rightWingTipTriangle.append(QPoint(+65, 100));
    rightWingTipTriangle.append(QPoint(+7, 130));
    QGraphicsPolygonItem *rightWingTip = new QGraphicsPolygonItem(this);
    rightWingTip->setPolygon(rightWingTipTriangle);
    rightWingTip->setBrush(QBrush(QColor(125, 125, 125)));
    rightWingTip->setPen(QPen(Qt::NoPen));
    rightWingTip->setPos(hitboxX_ / 2 - 1.8, 0);

    QPolygonF rightWingTriangle;
    rightWingTriangle.append(QPoint(+7, 50));
    rightWingTriangle.append(QPoint(+65, 100));
    rightWingTriangle.append(QPoint(+7, 130));
    QGraphicsPolygonItem *rightWing = new QGraphicsPolygonItem(this);
    rightWing->setPolygon(rightWingTriangle);
    rightWing->setBrush(QBrush(QColor(155, 155, 155)));
    rightWing->setPen(QPen(Qt::NoPen));
    rightWing->setPos(hitboxX_ / 2 - 1.8, 0);

    QPolygonF leftBodyTriangle;
    leftBodyTriangle.append(QPoint(-3, 20));
    leftBodyTriangle.append(QPoint(-35, 100));
    leftBodyTriangle.append(QPoint(-3, 130));
    QGraphicsPolygonItem *leftBody = new QGraphicsPolygonItem(this);
    leftBody->setPolygon(leftBodyTriangle);
    leftBody->setBrush(QBrush(QColor(185, 185, 185)));
    leftBody->setPen(QPen(Qt::NoPen));
    leftBody->setPos(hitboxX_ / 2 - 1.8, 0);

    QPolygonF rightBodyTriangle;
    rightBodyTriangle.append(QPoint(2, 20));
    rightBodyTriangle.append(QPoint(35, 100));
    rightBodyTriangle.append(QPoint(2, 130));
    QGraphicsPolygonItem *rightBody = new QGraphicsPolygonItem(this);
    rightBody->setPolygon(rightBodyTriangle);
    rightBody->setBrush(QBrush(QColor(185, 185, 185)));
    rightBody->setPen(QPen(Qt::NoPen));
    rightBody->setPos(hitboxX_ / 2 + 2.8, 0);

    QGraphicsEllipseItem *cockpit = new QGraphicsEllipseItem(this);
    int eW = 10;
    int eH = 30;
    cockpit->setRect(hitboxX_ / 2 - eW / 2, hitboxY_ - eH * 3, eW, eH);
    cockpit->setBrush(QBrush(QColor(255, 135, 0)));
    cockpit->setPen(QPen(Qt::NoPen));
}

QPoint Ship::getHitbox()
{
    return QPoint(hitboxX_, hitboxY_);
}

std::vector<Weapon *> Ship::getWeapons()
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

int Ship::getSpeed()
{
    return speed_;
}
