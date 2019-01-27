#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "player.h"
#include "soundcontroller.h"

#include <QGraphicsScene>
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>

class GameController : public QObject
{
Q_OBJECT
public:
    GameController(QGraphicsScene *scene, SoundController *s);
    ~GameController();

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void switchControl(QKeyEvent *e, bool b);

    /* Offensive control mechanisms of spaceship */
    void shoot();
    void superCharge();

    /* Spawning functions */
    void spawnAsteroid();
    void spawnScrap();
    void spawnStar();

    void pauseGame();
    bool gameIsPaused();

    Player* getPlayer();

    void setPointLabel(QLabel *points);
    void setHealthBar(std::vector<QGraphicsEllipseItem*> *healthBar);
    void setReloadBar(QGraphicsRectItem *reloadBar);
    void setReloadText(QLabel *reloadText);

private:
    QGraphicsScene *scene_;
    QLabel *points_;
    QGraphicsRectItem *reloadBar_;
    QLabel *reloadText_;

    SoundController *s_;

    QTimer *timer_;
    QTimer *scrapSpawner_;
    QTimer *asteroidSpawner_;
    QTimer *starsSpawner_;
    QTimer *cooldown_;

    Player *player_;

    int cooldownTimer_;

    bool gameIsPaused_;
    bool isOnCooldown_;
};
#endif // CONTROLLER_H
