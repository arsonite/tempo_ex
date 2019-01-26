#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsRectItem>
#include <QObject>

class Asteroid: public QObject, public QGraphicsRectItem
{
Q_OBJECT
public:
    Asteroid(int zValue);

private:
    void fly(bool outOfBounds);

    int speed_;

    double rotation_;

    bool collided_;
    bool isGold_;
};

#endif // ASTEROID_H
