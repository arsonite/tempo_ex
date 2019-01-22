#include "star.h"

#include <QGraphicsRectItem>
#include <QObject>

#include <stdlib.h>

#include <QPen>
#include <QTimer>

Star::Star()
{
    int random_number = rand() % 810;
    setPos(random_number, 0);

    int size = rand() % 5;
    setRect(0, 0, size, size);
    setPen(QPen(Qt::NoPen));
    setBrush(QColor(255, 255, 255));

    QTimer *timer = new QTimer();
    timer->setInterval(32);
    connect(timer, &QTimer::timeout, this, [=](){
        fly(y() + rect().height() >= 660);
    });
    timer->start();
}

void Star::fly(bool outOfBounds)
{
    if(outOfBounds) {
        delete this;
        return;
    }
    setPos(x(), y()+(rand() % 35));
}
