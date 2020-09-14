/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#include "player.h"
#include "projectile.h"

#include <iostream>

#include <QDebug>
#include <QPen>
#include <QSound>

/**
 * The player, represented by an internal <Ship> object.
 *
 * @brief Player::Player
 * @param shipC
 * @param weaponC
 * @param zValue
 */
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
    gameover_ = false;
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
    setX(this->x() + incr);
}

void Player::moveY(int incr)
{
    setY(this->y() + incr);
}

/**
 * Allows external manipulation by overriding the advance method of QGraphicsItem without
 * the need to cross-reference the player object with other objects.
 * Ensures clean code.
 *
 * @brief Player::advance
 * @param code
 */
void Player::advance(int code)
{
    if (code == 0 || code == 1 || code == 2)
        emit collected();
    switch (code)
    {
    case 0: //Health increase
        if (health_ >= MAX_HEALTH_)
            break;
        health_++;
        capsizeHealthBar();
        break;
    case 1: //Point multiplicator
        if (multiplicator_ == INT_MAX)
            return;
        multiplicator_ *= 2;
        //Prevents overflow
        if (multiplicator_ * 2 > INT_MAX)
            multiplicator_ = INT_MAX;
        multiplicatorLabel_->setVisible(true);
        multiplicatorLabel_->setText(QString::number(multiplicator_) + "x");
        break;
    case 2: //Point
        if (points_ == INT_MAX)
            return;
        points_ += (multiplicator_ * 1);
        //Prevents overflow
        if (points_ + 1 > INT_MAX)
            points_ = INT_MAX;
        break;
    case 3: //Health decrease
        health_--;
        capsizeHealthBar();
        multiplicator_ = 1;
        multiplicatorLabel_->setVisible(false);
        multiplicatorLabel_->setText(QString::number(multiplicator_) + "x");
        emit damaged(health_);
        if (health_ == 0)
        {
            gameover_ = true;
            emit valueChanged(gameover_);
        }
        break;
    }
}

void Player::capsizeHealthBar()
{
    for (int i = 0; i < healthBar_->size(); i++)
    {
        if (i <= health_ - 1)
        {
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
    int speed = s_->getSpeed();
    if (keysPressed_[0])
    {
        moveY(-speed);
    }
    if (keysPressed_[1])
    {
        moveY(speed);
    }
    if (keysPressed_[2])
    {
        moveX(-speed);
    }
    if (keysPressed_[3])
    {
        moveX(speed);
    }
    wallCollisionRedirect();
}

void Player::wallCollisionRedirect()
{
    int tempX = 900 - getShip()->getHitbox().x();
    int tempY = 700 - getShip()->getHitbox().y() - getShip()->getHitbox().y() / 2;
    if (x() > tempX)
    {
        x(tempX);
    }
    if (x() < 0)
    {
        x(0);
    }
    if (y() > tempY)
    {
        y(tempY);
    }
    if (y() < 0)
    {
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

void Player::setHealthBar(std::vector<QGraphicsEllipseItem *> *healthBar)
{
    healthBar_ = healthBar;
}

void Player::setMultiplicatorLabel(QLabel *multiplicatorLabel)
{
    multiplicatorLabel_ = multiplicatorLabel;
}
