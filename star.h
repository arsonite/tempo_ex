#ifndef STAR_H
#define STAR_H

#include <QGraphicsEllipseItem>
#include <QObject>

class Star: public QObject, public QGraphicsEllipseItem
{
Q_OBJECT
public:
    Star();

    void fly(bool outOfBounds);

private:
    int speed_;
};

#endif // STAR_H
