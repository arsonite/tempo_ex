#ifndef WEAPON_H
#define WEAPON_H

#include <QGraphicsRectItem>

class Weapon: public QGraphicsRectItem
{
public:
    Weapon(int c);

    void equipLaser();
    void equipCannon();
    void equipRockets();

private:
    int dmg_;
    int speed_;
    int fireRate_;
    int reloadTime_;
};

#endif // WEAPON_H
