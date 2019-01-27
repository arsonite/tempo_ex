#ifndef PLAYER_H
#define PLAYER_H

#include "ship.h"

#include <array>

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QLabel>

class Player: public QGraphicsRectItem
{
public:
    Player(int shipC, int weaponC, int zValue);

    double x() const;
    double y() const;

    void x(double x);
    void y(double y);

    void keyPress(int i, bool b);

    void moveX(int incr);
    void moveY(int incr);

    void advance(int dmg) override;
    void capsizeHealthBar();

    /* Collision detection */
    void wallCollisionRedirect();

    int getPoints();
    int getRemainingHealth();
    int getMaxHealth();

    void win();
    void loose();

    Ship *getShip();

    void setHealthBar(std::vector<QGraphicsEllipseItem*> *healthBar);
    void setMultiplicatorLabel(QLabel *multiplicatorLabel);

public slots:
    void moveShip();

private slots:
    QLabel *multiplicatorLabel_;

    Ship *s_;

    std::vector<QGraphicsEllipseItem*> *healthBar_;

    std::array<bool, 4> keysPressed_;

    int points_;
    int multiplicator_;
    int health_;
    int MAX_HEALTH_;
};

#endif // PLAYER_H
