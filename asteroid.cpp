#include "asteroid.h"
#include "player.h"

#include <stdlib.h>

#include <QPen>
#include <QTimer>
#include <QDebug>

Asteroid::Asteroid(int zValue)
{
    collided_ = false;

    setZValue(zValue);

    int random_number = rand() % 810;
    setPos(random_number, -100);

    bool randomizer = rand() % 2 == 0;

    speed_ = (rand() % 5) + (randomizer ? + 15 : + 5);
    rotation_ = (rand() % 1) + (randomizer ? + 1 : - 0.5);

    int size = (rand() % 50) + 50;
    setRect(0, 0, size, size);
    setPen(QPen(Qt::NoPen));

    int n = (rand() % 25) + 25;
    for(int i = 0; i < n; i++) {
        int rSize = rand() % size;
        int m = i + i;

        QPoint *q = new QPoint(size/2, size/2);
        QTransform *t = new QTransform();
        auto angle = rand() % 360;
        t->translate(q->x(), q->y());
        t->rotate(angle);
        t->translate(-q->x(), -q->y());

        if(i % 2 == 0) {
            QGraphicsRectItem *r = new QGraphicsRectItem(this);
            r->setRect(0, 0, rSize, rSize);
            r->setPos(t->map(r->pos()));
            r->setRotation(r->rotation() + angle);

            r->setPen(QPen(Qt::NoPen));
            r->setBrush(QBrush(QColor(60 + m, 0 + m, 0)));
            continue;
        }

        QGraphicsEllipseItem *e = new QGraphicsEllipseItem(this);
        e->setRect(0, 0, rSize, rSize);
        e->setPos(t->map(e->pos()));
        e->setRotation(e->rotation() + angle);

        e->setPen(QPen(Qt::NoPen));
        e->setBrush(QBrush(QColor(60 + m, 0 + m, 0)));
    }

    QTimer *timer = new QTimer();
    timer->setInterval(32);
    connect(timer, &QTimer::timeout, this, [=](){
        this->fly(y() + rect().height() >= 660 + size + 100);
    });
    timer->start();
}

void Asteroid::fly(bool outOfBounds)
{
    if(outOfBounds) {
        delete this;
        return;
    }

    setRotation(rotation() + rotation_);
    setPos(x(), y() + speed_);

    bool containsPlayer = false;
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0; i < colliding_items.size(); ++i) {
        if(typeid(*(colliding_items[i])) == typeid(Player)) {
            containsPlayer = true;
            if(collided_) return;
            colliding_items[i]->advance(-1);
            collided_ = true;
            return;
        }
    }
    if(!containsPlayer) collided_ = false;
}
