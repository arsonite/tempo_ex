#ifndef SCRAP_H
#define SCRAP_H

#include <QGraphicsRectItem>
#include <QObject>

class Scrap: public QObject, public QGraphicsRectItem
{
Q_OBJECT
public:
    Scrap();

    bool fly(bool outOfBounds);

    void advance(int dmg) override;

private:
    int health_;
    int speed_;
    int scraps_;
};

#endif // ASTEROID_H
