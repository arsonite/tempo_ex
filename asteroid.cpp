#include "asteroid.h"

#include <stdlib.h>

#include <QPen>
#include <QTimer>
#include <QDebug>

Asteroid::Asteroid()
{
    int random_number = rand() % 810;
    setPos(random_number, -50);
    qDebug() << random_number;

    int size = (rand() % 50)+50;
    setRect(0, 0, size, size);
    setPen(QPen(QColor(255, 0, 0)));

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
