#ifndef ENTITY_H
#define ENTITY_H

#include <QGraphicsRectItem>
#include <QObject>

class Entity: public QObject, public QGraphicsRectItem
{
Q_OBJECT
public:
    Entity();

protected:
    int speed_;
    int size_;
};

#endif // ENTITY_H
