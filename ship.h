/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#ifndef SHIP_H
#define SHIP_H

#include <weapon.h>

#include <vector>

#include <QGraphicsRectItem>

class Ship : public QGraphicsRectItem
{
public:
    Ship(int c, int weaponC, QGraphicsRectItem *parent);

    QPoint getHitbox();

    std::vector<Weapon *> getWeapons();

    int getClass();
    int getHealth();
    int getSpeed();

private:
    void constructRocket();
    void constructFighter();
    void constructCruiser();

    int hitboxX_;
    int hitboxY_;
    int c_;
    int weaponC_;
    int health_;
    int speed_;

    std::vector<Weapon *> weapons_;
};

#endif // SHIP_H
