/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#ifndef STAR_H
#define STAR_H

#include <QGraphicsEllipseItem>
#include <QObject>

class Star: public QObject, public QGraphicsEllipseItem
{
Q_OBJECT
public:
    Star(int zValue, bool &gameIsPaused);

    void fly(bool outOfBounds);

private:
    int speed_;

    bool &gameIsPaused_;
};

#endif // STAR_H
