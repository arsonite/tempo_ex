#include "player.h"
#include "projectile.h"

#include <iostream>

#include <QDebug>
#include <QPen>

Player::Player(int shipC, int weaponC, int zValue)
{
    setZValue(zValue);

    keysPressed_ = {false, false, false, false};
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    s_ = new Ship(shipC, weaponC, this);
    MAX_HEALTH_ = health_ = s_->getHealth();

    setRect(0, 0, 100, 50);

    points_ = 0;
    multiplicator_ = 1;
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

void Player::advance(int code)
{
    switch(code) {
        case 0: //Health increase
        if(health_ >= MAX_HEALTH_) break;
            health_++;
            capsizeHealthBar();
            break;
        case 1: //Point multiplicator
            if(multiplicator_ == INT_MAX) return;
            multiplicator_ *= 2;
            if(multiplicator_ * 2 > INT_MAX) multiplicator_ = INT_MAX;
            multiplicatorLabel_->setVisible(true);
            multiplicatorLabel_->setText(QString::number(multiplicator_) + "x");
            break;
        case 2: //Point
            if(points_ == INT_MAX) return;
            points_+= (multiplicator_ * 1);
            if(points_ + 1 > INT_MAX) points_ = INT_MAX;
            break;
        case 3: //Health decrease
            if(health_ <= 0) return;
            health_--;
            capsizeHealthBar();
            break;
        case 4: //Reset multiplier
            multiplicator_ = 1;
            multiplicatorLabel_->setVisible(false);
            multiplicatorLabel_->setText(QString::number(multiplicator_) + "x");
            break;
    }
}

void Player::capsizeHealthBar()
{
    for(int i = 0; i < healthBar_->size(); i++) {
        if(i <= health_-1) {
            healthBar_->at(i)->setBrush(QBrush(QColor(255, 75, 75)));
            continue;
        }
        healthBar_->at(i)->setBrush(QBrush(QColor(50, 0, 0)));
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
}

void Player::wallCollisionRedirect()
{
    int tempX = 900-getShip()->getHitbox().x();
    int tempY = 700-getShip()->getHitbox().y()-getShip()->getHitbox().y()/2;
    if(x() > tempX) {
        x(tempX);
    }
    if(x() < 0) {
        x(0);
    }
    if(y() > tempY) {
        y(tempY);
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

void Player::setHealthBar(std::vector<QGraphicsEllipseItem*> *healthBar)
{
    healthBar_ = healthBar;
}

void Player::setMultiplicatorLabel(QLabel *multiplicatorLabel)
{
    multiplicatorLabel_ = multiplicatorLabel;
}

