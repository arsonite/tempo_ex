#include "projectile.h"
#include "scrap.h"
#include "asteroid.h"

#include <QPen>
#include <QTimer>

#include <QDebug>

Projectile::Projectile(int zValue, int modifier, bool &gameIsPaused, Weapon *w): modifier_(modifier), gameIsPaused_(gameIsPaused), w_(w)
{
    setZValue(zValue);

    setBrush(QBrush(QColor(250, 250, 50)));
    setPen(QPen(Qt::NoPen));

    QTimer *timer = new QTimer();
    timer->setInterval(32);

    connect(timer, &QTimer::timeout, this, [=](){
        fly(y() + rect().height() + 20 < 0);
    });
    timer->start();
}

void Projectile::fly(bool outOfBounds)
{
    if(gameIsPaused_) return;

    if(outOfBounds) {
        delete this;
        return;
    }

    setPos(x()+w_->getSpeed().x() + modifier_, y()-w_->getSpeed().y());

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
