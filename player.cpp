#include "player.h"
#include "projectile.h"

#include <iostream>

#include <QDebug>
#include <QPen>

Player::Player()
{
    keysPressed_ = {false, false, false, false};
    setFlag(QGraphicsItem::ItemIsFocusable);

    setRect(0, 0, 100, 100);
    setPen(QPen(QColor(255, 0, 0)));

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

void Player::advance(int point)
{
    points_+= point;
    qDebug() << "Player has: " << points_;

    if(points_ < 0) {
        //delete this; // better solution so game doesnt crash
        qDebug() << "PLAYER IS DEAD!!!!";
    }
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
    qDebug() << "moveShip(" << "x: " << x() << ", y: " << y() << ")";
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
