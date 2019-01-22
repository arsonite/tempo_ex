#include "scrap.h"

#include <stdlib.h>

#include <QPen>
#include <QTimer>
#include <QDebug>

Scrap::Scrap()
{
    int random_number = rand() % 810;
    setPos(random_number, -100);

    int size = (rand() % 50) + 50;
    health_ = size;
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

bool Scrap::fly(bool outOfBounds)
{
    if(outOfBounds) {
        delete this;
        qDebug() << "Asteroid deleted.";
        return true;
    }
    setPos(x(), y() + 5);
    return false;
}

void Scrap::advance(int dmg)
{
    int oldValue = health_;
    health_-= dmg;

    if(health_ <= 0) {
        delete this;
        return;
    }

    double n = scraps_ * (((health_ * 100.0) / oldValue) / 100.0);
    scraps_ = int (n);
    for(int i = 0; i < childItems().size(); i++) {
        if(i > n) {
            continue;
        }
        delete childItems().at(i);
    }
}
