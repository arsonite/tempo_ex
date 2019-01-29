/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#include "scrap.h"
#include "player.h"

#include <stdlib.h>

#include <QPen>
#include <QTimer>
#include <QDebug>

Scrap::Scrap(int zValue, bool &gameIsPaused): gameIsPaused_(gameIsPaused)
{
    setZValue(zValue);

    collided_ = false;
    destroyed_ = false;

    int random_number = rand() % 810;
    setPos(random_number, -100);

    MAX_HEALTH_ = health_ = size_ = (rand() % 50) + 50;
    setRect(0, 0, size_, size_);
    setPen(QPen(Qt::NoPen));

    int n = (rand() % 10) + 10;
    scraps_ = n;
    for(int i = 0; i < n; i++) {
        QGraphicsRectItem *r = new QGraphicsRectItem(this);
        int xSize = (rand() % size_);
        int ySize = (rand() % size_);

        QPoint *q = new QPoint(size_/2, size_/2);
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
        this->fly(y() + rect().height() >= 660 + size_);
    });
    timer->start();
}

void Scrap::fly(bool outOfBounds)
{
    if(gameIsPaused_) return;

    if(outOfBounds) {
        delete this;
        return;
    }

    setPos(x(), y() + ((rand() % 3) + 2));

    bool containsPlayer = false;
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0; i < colliding_items.size(); ++i) {
        if(typeid(*(colliding_items[i])) == typeid(Player)) {
            containsPlayer = true;
            if(destroyed_) {
                colliding_items[i]->advance(2); //Increase points by one
                delete this;
                return;
            }
            if(collided_) return;
            colliding_items[i]->advance(3); //Decrease Health by one
            collided_ = true;
            return;
        }
    }
    if(!containsPlayer) collided_ = false;
}

void Scrap::advance(int dmg)
{
    if(destroyed_) return;

    health_-= dmg;

    double n = scraps_ * (((health_ * 100.0) / MAX_HEALTH_) / 100.0);
    scraps_ = n < 0 ? 0 : int (n);
    for(int i = 0; i < childItems().count(); i++) {
        if(i > scraps_) break;
        delete childItems().at(i);
    }

    if(scraps_ <= 0) {
        destroyed_ = true;
        dropPoint();
        return;
    }
}

void Scrap::dropPoint()
{
    while(childItems().count() > 0) delete childItems().first();

    QGraphicsEllipseItem *point = new QGraphicsEllipseItem(this);
    int pointWidth = 20;
    point->setRect(size_/2-pointWidth/2, size_/2-pointWidth/2, pointWidth, pointWidth);
    point->setBrush(QBrush(QColor(0, 255, 0)));
    point->setPen(QPen(Qt::NoPen));
}

bool Scrap::isDestroyed()
{
    return destroyed_;
}
