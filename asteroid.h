#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsRectItem>
#include <QObject>

class Asteroid: public QObject, public QGraphicsRectItem
{
Q_OBJECT
public:
    Asteroid(int zValue);

    void fly(bool outOfBounds);

    void advance(int dmg);
    void drop();

    bool isDestroyed();

private:
    int size_;
    int speed_;
    int scraps_;
    int drop_;
    int health_;
    int MAX_HEALTH_;

    double rotation_;

    bool collided_;
    bool destroyed_;
    bool isGold_;
};

#endif // ASTEROID_H
