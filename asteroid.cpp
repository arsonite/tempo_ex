#include "asteroid.h"
#include "player.h"

#include <stdlib.h>

#include <QPen>
#include <QTimer>
#include <QDebug>
#include <QFontDatabase>

Asteroid::Asteroid(int zValue)
{
    setZValue(zValue);

    collided_ = false;
    destroyed_ = false;

    /* Gold Asteroid */
    isGold_ = rand() % 100 < 100;
    speed_ = (rand() % 2) + (isGold_ ? + 3 : + 18);
    rotation_ = (rand() % 1) + (isGold_ ? - 0.5 : + 1);

    int pos = rand() % 810;
    setPos(pos, -100);
    MAX_HEALTH_ = health_ = size_ = (rand() % 50) + 50;
    setRect(0, 0, size_, size_);
    setPen(QPen(Qt::NoPen));

    int n = (rand() % 25) + 25;
    scraps_ = n;
    for(int i = 0; i < n; i++) {
        int rSize = rand() % size_;
        int m = i + i;

        QPoint *q = new QPoint(size_/2, size_/2);
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

            if(isGold_) {
                r->setBrush(QBrush(QColor(120 + m, 100 + m, 0)));
            } else {
                r->setBrush(QBrush(QColor(60 + m, 0 + m, 0)));
            }
            continue;
        }

        QGraphicsEllipseItem *e = new QGraphicsEllipseItem(this);
        e->setRect(0, 0, rSize, rSize);
        e->setPos(t->map(e->pos()));
        e->setRotation(e->rotation() + angle);
        e->setPen(QPen(Qt::NoPen));

        if(isGold_) {
            e->setBrush(QBrush(QColor(120 + m, 100 + m, 0)));
        } else {
            e->setBrush(QBrush(QColor(60 + m, 0 + m, 0)));
        }
    }

    QTimer *timer = new QTimer();
    timer->setInterval(32);
    connect(timer, &QTimer::timeout, this, [=](){
        this->fly(y() + rect().height() >= 660 + size_ + 100);
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
            if(destroyed_) {
                colliding_items[i]->advance(drop_);
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

void Asteroid::advance(int dmg)
{
    if(!isGold_ || destroyed_) return;

    health_-= dmg;
    double n = scraps_ * (((health_ * 100.0) / MAX_HEALTH_) / 100);
    scraps_ = n < 0 ? 0 : int (n);
    for(int i = 0; i < childItems().count(); i++) {
        if(i <= scraps_) {
            delete childItems().at(i);
        }
    }

    if(scraps_ <= 0) {
        destroyed_ = true;
        drop();
        return;
    }
}

void Asteroid::drop()
{
    while(childItems().count() > 0) delete childItems().first();

    drop_ = (rand() % 100) / 50;
    if(drop_ == 0) {
        QGraphicsEllipseItem *health = new QGraphicsEllipseItem(this);
        int pointWidth = 20;
        health->setRect(size_/2-pointWidth/2, size_/2-pointWidth/2, pointWidth, pointWidth);
        health->setBrush(QBrush(QColor(255, 75, 75)));
        health->setPen(QPen(Qt::NoPen));
        return;
    }
    /* Font anders lösen, redundanz */
    int id = QFontDatabase::addApplicationFont(":/res/res/8-Bit Wonder.TTF");
    QString customFont = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont bit(customFont);
    bit.setPointSize(20);
    QGraphicsTextItem *multi = new QGraphicsTextItem("2X");
    multi->setFont(bit);
    multi->setParentItem(this);
    multi->setPos(size_/2-20/2, size_/2-20/2);
}

bool Asteroid::isDestroyed()
{
    return destroyed_;
}
