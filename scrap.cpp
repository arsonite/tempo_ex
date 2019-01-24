#include "scrap.h"
#include "player.h"

#include <stdlib.h>

#include <QPen>
#include <QTimer>
#include <QDebug>

Scrap::Scrap()
{
    destroyed_ = false;

    int random_number = rand() % 810;
    setPos(random_number, -100);

    int size = (rand() % 50) + 50;
    size_ = size;
    oldValue_ = health_ = size;
    setRect(0, 0, size, size);
    //setPen(QPen(QColor(255, 0, 0)));
    setPen(QPen(Qt::NoPen));

    int n = (rand() % 10) + 10;
    scraps_ = n;
    for(int i = 0; i < n; i++) {
        QGraphicsRectItem *r = new QGraphicsRectItem(this);
        int xSize = (rand() % size);
        int ySize = (rand() % size);

        QPoint *q = new QPoint(size/2, size/2);
        QTransform *t = new QTransform();
        auto angle = rand() % 360;
        t->translate(q->x(), q->y());
        t->rotate(angle);
        t->translate(-q->x(), -q->y());
        r->setRect(0, 0, xSize, ySize);
        r->setPos(t->map(r->pos()));
        r->setRotation(r->rotation() + angle);

        r->setPen(QPen(Qt::NoPen));
        int greyscale = 50 + (i * 10);
        r->setBrush(QBrush(QColor(greyscale, greyscale, greyscale)));
    }

    QTimer *timer = new QTimer();
    timer->setInterval(32);
    connect(timer, &QTimer::timeout, this, [=](){
        this->fly(y() + rect().height() >= 660 + size);
    });
    timer->start();
}

void Scrap::fly(bool outOfBounds)
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

    setPos(x(), y() + ((rand() % 3) + 2));
    return;
}

void Scrap::advance(int dmg)
{
    if(destroyed_) {
        return;
    }

    health_-= dmg;

    if(health_ <= 0) {
        destroyed_ = true;
        dropPoint();
        return;
    }

    double n = scraps_ * (((health_ * 100.0) / oldValue_) / 100);
    scraps_ = int (n);
    for(int i = 0; i < childItems().size(); i++) {
        if(i <= scraps_) {
            delete childItems().at(i);
        }
    }
}

void Scrap::dropPoint()
{
    QGraphicsEllipseItem *point = new QGraphicsEllipseItem(this);
    point->setRect(size_/2, size_/2, 20, 20);
    point->setBrush(QBrush(QColor(0, 255, 0)));
    point->setPen(QPen(Qt::NoPen));
}
