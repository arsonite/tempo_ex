#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"

#include <QGraphicsScene>
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>

class GameController : public QObject
{
Q_OBJECT
public:
    GameController(QGraphicsScene &scene, QLabel &points);
    ~GameController();

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void switchControl(QKeyEvent *e, bool b);

    void shoot();
    void useSpecial();
    void superCharge();

    void spawnAsteroid();
    void spawnScrap();
    void spawnStar();

private:
    QGraphicsScene *scene_;
    QLabel *points_;

    QTimer *timer_;

    Player *player_;
};
#endif // CONTROLLER_H
