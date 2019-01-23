#include "asteroid.h"
#include "player.h"

#include <stdlib.h>

#include <QPen>
#include <QTimer>
#include <QDebug>

Asteroid::Asteroid()
{
    int random_number = rand() % 810;
    setPos(random_number, -100);

    int size = (rand() % 50) + 50;
    setRect(0, 0, size, size);
    setPen(QPen(Qt::NoPen));

    int n = (rand() % 10) + 10;
    for(int i = 0; i < n; i++) {
        QGraphicsRectItem *r = new QGraphicsRectItem(this);
        int rSize = (rand() % size);

        QPoint *q = new QPoint(size/2, size/2);
        QTransform *t = new QTransform();
        auto angle = rand() % 360;
        t->translate(q->x(), q->y());
        t->rotate(angle);
        t->translate(-q->x(), -q->y());
        r->setRect(0, 0, rSize, rSize);
        r->setPos(t->map(r->pos()));
        r->setRotation(r->rotation() + angle);

        r->setPen(QPen(Qt::NoPen));
        int m = i * 2;
        r->setBrush(QBrush(QColor(120 + m, 50 + m, 0 + m)));
    }

    QTimer *timer = new QTimer();
    timer->setInterval(32);
    connect(timer, &QTimer::timeout, this, [=](){
        this->fly(y() + rect().height() >= 660 + size);
    });
    timer->start();
}

void Asteroid::fly(bool outOfBounds)
{
    if(outOfBounds) {
        delete this;
        qDebug() << "Asteroid deleted.";
        return;
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0; i < colliding_items.size(); ++i) {
        if(typeid(*(colliding_items[i])) == typeid(Player)) {
            if(destroyed_) {
                colliding_items[i]->advance(1);
                delete this;
                return;
            }
            colliding_items[i]->advance(-1);
        }
    }

    setPos(x(), y() + 5);
    return;
}
