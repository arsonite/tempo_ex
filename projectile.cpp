/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#include "projectile.h"
#include "scrap.h"
#include "asteroid.h"

#include <QPen>
#include <QTimer>

#include <QDebug>

/**
 * The <Projectile> class is responsible for damaging and destroying other objects.
 *
 * @brief Projectile::Projectile
 * @param zValue
 * @param modifier
 * @param gameIsPaused
 * @param w
 */
Projectile::Projectile(int zValue, int modifier, bool &gameIsPaused, Weapon *w): modifier_(modifier), gameIsPaused_(gameIsPaused), w_(w)
{
    setZValue(zValue);

    setBrush(QBrush(QColor(250, 250, 50)));
    setPen(QPen(Qt::NoPen));

    QTimer *timer = new QTimer();
    timer->setInterval(32);

    connect(timer, &QTimer::timeout, this, [=](){
        /* Conditional statement to determine wether projectile left world boundaries */
        fly(y() + rect().height() + 20 < 0);
    });
    timer->start();
}

void Projectile::fly(bool outOfBounds)
{
    /* Halts the movement of the projectile when the game is paused */
    if(gameIsPaused_) return;

    /* If the projectile is out of the predefined world bounds, it gets deleted */
    if(outOfBounds) {
        delete this;
        return;
    }

    /* */
    setPos(x()+w_->getSpeed().x() + modifier_, y()-w_->getSpeed().y());

    /* */
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0; i < colliding_items.size(); ++i) {
        if(typeid(*(colliding_items[i])) == typeid(Scrap)) {
            if(static_cast<Scrap*>(colliding_items[i])->isDestroyed()) continue;
            colliding_items[i]->advance(w_->getDamage());
            delete this;
            return;
        } else if(typeid(*(colliding_items[i])) == typeid(Asteroid)) {
            if(static_cast<Asteroid*>(colliding_items[i])->isDestroyed()) continue;
            colliding_items[i]->advance(w_->getDamage());
            delete this;
            return;
        }
    }
}
