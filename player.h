#ifndef PLAYER_H
#define PLAYER_H

#include "ship.h"

#include <array>

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QLabel>

class Player: public QObject, public QGraphicsRectItem
{
Q_OBJECT
public:
    explicit Player(int shipC, int weaponC, int zValue);
    virtual ~Player() override {}

    double x() const;
    double y() const;

    void x(double x);
    void y(double y);

    void keyPress(int i, bool b);

    void moveX(int incr);
    void moveY(int incr);

    void capsizeHealthBar();

    /* Collision detection */
    void wallCollisionRedirect();

    int getPoints();
    int getRemainingHealth();
    int getMaxHealth();

    Ship *getShip();

    void setHealthBar(std::vector<QGraphicsEllipseItem*> *healthBar);
    void setMultiplicatorLabel(QLabel *multiplicatorLabel);

public slots:
    void moveShip();

    void advance(int dmg) override;

signals:
    void valueChanged(int value);

private:
    QLabel *multiplicatorLabel_;

    Ship *s_;

    std::vector<QGraphicsEllipseItem*> *healthBar_;

    std::array<bool, 4> keysPressed_;

    int points_;
    int multiplicator_;
    int health_;
    int MAX_HEALTH_;

    bool gameover_;
};

#endif // PLAYER_H
