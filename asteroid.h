#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsRectItem>
#include <QObject>

class Asteroid: public QObject, public QGraphicsRectItem
{
Q_OBJECT
public:
    Asteroid();

    void fly(bool outOfBounds);

private:
    int size_;
    int speed_;
};

#endif // ASTEROID_H
