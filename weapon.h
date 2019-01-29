/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#ifndef WEAPON_H
#define WEAPON_H

#include <QGraphicsRectItem>

class Weapon: public QGraphicsRectItem
{
public:
    Weapon(QGraphicsRectItem *parent, int c, int x, int y);

    void setSpeed(QPoint speed);
    QPoint getSpeed();

    int getClass();
    int getDamage();
    int getReloadTime();

private:
    QPoint speed_;

    int height_;
    int width_;
    int c_;
    int x_;
    int y_;
    int dmg_;
    int reloadTime_;
};

#endif // WEAPON_H
