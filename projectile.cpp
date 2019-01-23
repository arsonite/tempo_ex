#include "projectile.h"
#include "scrap.h"
#include "asteroid.h"

#include <QPen>
#include <QTimer>

#include <QDebug>

Projectile::Projectile(int speed, int dmg): speed_(speed), dmg_(dmg)
{
    setRect(90/2, -50, 10, 50);
    setPen(QPen(QColor(255, 0, 0)));

    QTimer *timer = new QTimer();
    timer->setInterval(32);

    connect(timer, &QTimer::timeout, this, [=](){
        fly(y() + rect().height() < 0);
    });

    timer->start();
}

void Projectile::fly(bool outOfBounds)
{
    if(outOfBounds) {
        delete this;
        qDebug() << "Projectile deleted.";
        return;
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0; i < colliding_items.size(); ++i) {
        if(typeid(*(colliding_items[i])) == typeid(Scrap)
                || typeid(*(colliding_items[i])) == typeid(Asteroid)) {
            colliding_items[i]->advance(dmg_);
            delete this;
            return;
        }
    }
    setPos(x(), y()-speed_);
}
