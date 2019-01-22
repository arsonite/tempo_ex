#include "asteroid.h"

#include <stdlib.h>

#include <QPen>
#include <QTimer>
#include <QDebug>

Asteroid::Asteroid()
{
    int random_number = rand() % 810;
    setPos(random_number, -50);

    int size = (rand() % 50)+50;
    health_ = size;
    setRect(0, 0, size, size);
    setPen(QPen(QColor(255, 0, 0)));
    //setPen(QPen(Qt::NoPen));

    for(int i = 0; i < 10; i++) {
        QGraphicsRectItem *r = new QGraphicsRectItem(this);
        int rSize = (rand() % (size*2 + 1 - size/2)) + size/2;
        r->setRect(rSize, rSize, size/10, size/10);
        r->setRotation(rand() % 90);
        r->setPen(QPen(Qt::NoPen));
        r->setBrush(QBrush(QColor(129+i*2, 59+i*2, 9+i*2)));
    }

    QTimer *timer = new QTimer();
    timer->setInterval(32);
    connect(timer, &QTimer::timeout, this, [=](){
        this->fly(y() + rect().height() >= 660 + size);
    });
    timer->start();
}

bool Asteroid::fly(bool outOfBounds)
{
    if(outOfBounds) {
        delete this;
        qDebug() << "Asteroid deleted.";
        return true;
    }
    setPos(x(), y()+5);
    return false;
}
