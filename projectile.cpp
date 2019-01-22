#include "projectile.h"

#include <QPen>
#include <QTimer>

#include <QDebug>

Projectile::Projectile()
{
    setRect(90/2, -50, 10, 50);
    setPen(QPen(QColor(255, 0, 0)));

    QTimer *timer = new QTimer();
    timer->setInterval(32);

    connect(timer, &QTimer::timeout, this, [=](){
        this->fly(y() + rect().height() < 0);
    });

    timer->start();
}

bool Projectile::fly(bool outOfBounds)
{
    if(outOfBounds) {
        delete this;
        qDebug() << "Projectile deleted.";
        return true;
    }
    setPos(x(), y()-10);
    return false;
}
