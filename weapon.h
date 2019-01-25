#ifndef WEAPON_H
#define WEAPON_H

#include <QGraphicsRectItem>

class Weapon: public QGraphicsRectItem
{
public:
    Weapon(QGraphicsRectItem *parent, int c, int x, int y);

    void equipLaser();
    void equipCannon();
    void equipRockets();

private:
    int height_;
    int width_;
    int c_;
    int x_;
    int y_;
    int dmg_;
    int speed_;
    int fireRate_;
    int reloadTime_;
};

#endif // WEAPON_H
