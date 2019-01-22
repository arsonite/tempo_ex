#ifndef PLAYER_H
#define PLAYER_H

#include <array>

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

class Player: public QGraphicsRectItem
{
public:
    Player();

    double x() const;
    double y() const;

    void x(double x);
    void y(double y);

    void keyPress(int i, bool b);

    void moveX(int incr);
    void moveY(int incr);
    void increasePoints();
    void decreasePoints();

    /* Collision detection */
    void wallCollisionRedirect();
    bool asteroidCollision();
    bool enemyCollision();
    bool projectileCollision();

    void win();
    void loose();

public slots:
    void moveShip();

private slots:
    std::array<bool, 4> keysPressed_;
};

#endif // PLAYER_H
