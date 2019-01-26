#include "player.h"
#include "projectile.h"

#include <iostream>

#include <QDebug>
#include <QPen>

Player::Player(int shipC, int zValue)
{
    setZValue(zValue);

    keysPressed_ = {false, false, false, false};
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    s_ = new Ship(shipC, this);
    MAX_HEALTH_ = health_ = s_->getHealth();

    setRect(0, 0, 100, 50);

    points_ = 0;
}

double Player::x() const
{
    return pos().x();
}

double Player::y() const
{
    return pos().y();
}

void Player::x(double x)
{
    setX(x);
}

void Player::y(double y)
{
    setY(y);
}

void Player::moveX(int incr)
{
    setX(this->x()+incr);
}

void Player::moveY(int incr)
{
    setY(this->y()+incr);
}

void Player::advance(int i)
{
    if(i < 0) {
        health_--;
        qDebug() << health_;
        return;
    }
    points_++;
}

void Player::keyPress(int i, bool b)
{
    keysPressed_[i] = b;
}

void Player::moveShip()
{
    if(keysPressed_[0]) {
        moveY(-10);
    }
    if(keysPressed_[1]) {
        moveY(10);
    }
    if(keysPressed_[2]) {
        moveX(-10);
    }
    if(keysPressed_[3]) {
        moveX(10);
    }
    wallCollisionRedirect();
}

void Player::wallCollisionRedirect()
{
    if(x() > 910-100) {
        x(910-100);
    }
    if(x() < 0) {
        x(0);
    }
    if(y() > 660-100) {
        y(660-100);
    }
    if(y() < 0) {
        y(0);
    }
}

int Player::getPoints()
{
    return points_;
}

int Player::getRemainingHealth()
{
    return health_;
}

int Player::getMaxHealth()
{
    return MAX_HEALTH_;
}

Ship *Player::getShip()
{
    return s_;
}
