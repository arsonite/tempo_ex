/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#include "asteroid.h"
#include "player.h"

#include <stdlib.h>

#include <QPen>
#include <QTimer>
#include <QDebug>
#include <QFontDatabase>

/**
 * A randomly generated <QGraphicsRectItem> that is supposed to resemble an
 * extraterrestial celestial body, an asteroid.
 * There is a small calculated chance, that the <Asteroid> object has a golden
 * paint on it, meaning the player can destroy it and receive goodies.
 * The asteroid itself detects collision with the <Player> object and the surrounding
 * game boundaries defined by the window width and height.
 *
 * @brief Asteroid::Asteroid
 * @param zValue, the z-value that determines the lateral order in the view
 * @param gameIsPaused
 */
Asteroid::Asteroid(int zValue, bool &gameIsPaused) : gameIsPaused_(gameIsPaused)
{
    setZValue(zValue);

    collided_ = false;
    destroyed_ = false;

    /* Determining the chance of the asteroid becoming a golden one */
    isGold_ = rand() % 100 < 25;
    speed_ = (rand() % 2) + (isGold_ ? +3 : +18);
    rotation_ = (rand() % 1) + (isGold_ ? -0.5 : +1);

    int pos = rand() % 810;
    setPos(pos, -100);
    MAX_HEALTH_ = health_ = size_ = (rand() % 50) + 50;
    setRect(0, 0, size_, size_);
    setPen(QPen(Qt::NoPen));

    int n = (rand() % 25) + 25; //The amount of smaller bodies inside the hitbox
    scraps_ = n;
    for (int i = 0; i < n; i++)
    {
        int rSize = rand() % size_;
        int m = i + i; //Lighting-modifier for the color

        /* Necessary steps to ensure the asteroid rotates around its centre */
        QPoint *q = new QPoint(size_ / 2, size_ / 2);
        QTransform *t = new QTransform();
        auto angle = rand() % 360;
        t->translate(q->x(), q->y());
        t->rotate(angle);
        t->translate(-q->x(), -q->y());

        /* If i is even, create a sphere instead of a rectangle */
        if (i % 2 == 0)
        {
            QGraphicsRectItem *r = new QGraphicsRectItem(this);
            r->setRect(0, 0, rSize, rSize);
            r->setPos(t->map(r->pos()));
            r->setRotation(r->rotation() + angle);
            r->setPen(QPen(Qt::NoPen));

            if (isGold_)
            {
                r->setBrush(QBrush(QColor(120 + m, 100 + m, 0)));
            }
            else
            {
                r->setBrush(QBrush(QColor(60 + m, 0 + m, 0)));
            }
            continue;
        }

        QGraphicsEllipseItem *e = new QGraphicsEllipseItem(this);
        e->setRect(0, 0, rSize, rSize);
        e->setPos(t->map(e->pos()));
        e->setRotation(e->rotation() + angle);
        e->setPen(QPen(Qt::NoPen));

        if (isGold_)
        {
            e->setBrush(QBrush(QColor(120 + m, 100 + m, 0)));
        }
        else
        {
            e->setBrush(QBrush(QColor(60 + m, 0 + m, 0)));
        }
    }

    QTimer *timer = new QTimer();
    timer->setInterval(32);
    connect(timer, &QTimer::timeout, this, [=]() {
        /* Conditional statement to determine wether asteroid left world boundaries */
        this->fly(y() + rect().height() >= 660 + size_ + 100);
    });
    timer->start();
}

/**
 * Animates the flight path and rotation of the singular asteroid.
 *
 * @brief Asteroid::fly
 * @param outOfBounds
 */
void Asteroid::fly(bool outOfBounds)
{
    if (gameIsPaused_)
        return;

    if (outOfBounds)
    {
        delete this;
        return;
    }

    setRotation(rotation() + rotation_);
    setPos(x(), y() + speed_);

    /* Retrieve all QGraphicsItems that collide with the asteroid */
    bool containsPlayer = false;
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i)
    {
        /* Determines wether the collided item is the <Player> object */
        if (typeid(*(colliding_items[i])) == typeid(Player))
        {
            containsPlayer = true;
            /* If the asteroid is destroyed, add health or a multiplier to the player */
            if (destroyed_)
            {
                colliding_items[i]->advance(drop_);
                delete this;
                return;
            }
            if (collided_)
                return;                     //Prohibits continoues collision detection
            colliding_items[i]->advance(3); //Decrease player health by one and reset multiplier
            collided_ = true;
            return;
        }
    }
    if (!containsPlayer)
        collided_ = false;
}

/**
 * Overriden method determining remaining health of asteroid after getting hit
 * by a <Projectile> object.
 *
 * @brief Asteroid::advance
 * @param dmg
 */
void Asteroid::advance(int dmg)
{
    if (!isGold_ || destroyed_)
        return;

    health_ -= dmg;
    /* Calculates the percentage of smaller QGraphicsItems that have to be deleted
     * in dependency of the asteroids remaining health
     */
    double n = scraps_ * (((health_ * 100.0) / MAX_HEALTH_) / 100);
    scraps_ = n < 0 ? 0 : int(n);
    /* Deletes all the childitems up until the calculated percentage */
    for (int i = 0; i < childItems().count(); i++)
    {
        if (i <= scraps_)
        {
            delete childItems().at(i);
        }
    }

    if (scraps_ <= 0)
    {
        destroyed_ = true;
        drop();
        return;
    }
}

/**
 * Determines by chance which items to drop if asteroid is gold.
 *
 * @brief Asteroid::drop
 */
void Asteroid::drop()
{
    /* Deletes the remaining childitems */
    while (childItems().count() > 0)
        delete childItems().first();

    /* Calculates wether the (golden) asteroid should drop health or a multiplier */
    drop_ = (rand() % 99) / 50;
    if (drop_ == 0)
    {
        QGraphicsEllipseItem *health = new QGraphicsEllipseItem(this);
        int pointWidth = 20;
        health->setRect(size_ / 2 - pointWidth / 2, size_ / 2 - pointWidth / 2, pointWidth, pointWidth);
        health->setBrush(QBrush(QColor(255, 75, 75)));
        health->setPen(QPen(Qt::NoPen));
        return;
    }
    /* Rather redudant font implementation */
    int id = QFontDatabase::addApplicationFont(":/res/res/8-Bit Wonder.TTF");
    QString customFont = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont bit(customFont);
    bit.setPointSize(20);
    QGraphicsTextItem *multi = new QGraphicsTextItem("2X");
    multi->setFont(bit);
    multi->setParentItem(this);
    multi->setPos(size_ / 2 - 20 / 2, size_ / 2 - 20 / 2);
}

bool Asteroid::isDestroyed()
{
    return destroyed_;
}
