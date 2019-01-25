#include "weapon.h"

Weapon::Weapon(int c)
{
    switch(c) {
        case 1:
            equipLaser();
            break;
        case 2:
            equipCannon();
            break;
        case 3:
            equipRockets();
            break;
    }
}

void Weapon::equipLaser()
{

}

void Weapon::equipCannon()
{

}

void Weapon::equipRockets()
{

}
