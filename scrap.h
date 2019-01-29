/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#ifndef SCRAP_H
#define SCRAP_H

#include <QGraphicsRectItem>
#include <QObject>

class Scrap: public QObject, public QGraphicsRectItem
{
Q_OBJECT
public:
    Scrap(int zValue, bool &gameIsPaused);

    void fly(bool outOfBounds);

    void advance(int dmg) override; //Overriding to prevent need for typecasting

    void dropPoint();

    bool isDestroyed();

private:
    int size_;
    int speed_;
    int scraps_;
    int health_;
    int MAX_HEALTH_;

    bool &gameIsPaused_;
    bool collided_;
    bool destroyed_;
};

#endif // SCRAP_H
