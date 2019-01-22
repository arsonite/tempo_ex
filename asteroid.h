#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsRectItem>
#include <QObject>

class Asteroid: public QObject, public QGraphicsRectItem
{
Q_OBJECT
public:
    Asteroid();

    bool fly(bool outOfBounds);
};

#endif // ASTEROID_H
