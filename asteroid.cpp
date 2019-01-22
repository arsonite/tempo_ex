#include "asteroid.h"

#include <stdlib.h>

#include <QPen>
#include <QTimer>
#include <QDebug>

Asteroid::Asteroid()
{
    int random_number = rand() % 700;
    setPos(random_number, 0);

    setRect(0, 0, 50, 50);
    setPen(QPen(QColor(255, 0, 0)));

    QTimer *timer = new QTimer();
    timer->setInterval(32);
    connect(timer, &QTimer::timeout, this, [=](){
        this->fly(y() + rect().height() >= 600);
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
    setPos(x(), y()-5);
    return false;
}
