#ifndef SCRAP_H
#define SCRAP_H

#include <QGraphicsRectItem>
#include <QObject>

class Scrap: public QObject, public QGraphicsRectItem
{
Q_OBJECT
public:
    Scrap(int zValue);

    void fly(bool outOfBounds);

    void advance(int dmg) override;

    void dropPoint();

private:
    int size_;
    int health_;
    int speed_;
    int scraps_;
    int oldValue_;

    bool collided_;
    bool destroyed_;
};

#endif // SCRAP_H
