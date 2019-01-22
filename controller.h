#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"

#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>

class Controller : public QObject
{
Q_OBJECT
public:
    Controller(QGraphicsScene &scene);
    ~Controller();

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void switchControl(QKeyEvent *e, bool b);

    void shoot();
    void useSpecial();
    void superCharge();

private:
    QGraphicsScene *scene_;
    QTimer *timer_;

    Player *player_;
};
#endif // CONTROLLER_H
