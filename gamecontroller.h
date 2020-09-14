/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
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

    /* Offensive control mechanism of spaceship */
    void shoot();

    /* Spawning functions */
    void spawnAsteroid();
    void spawnScrap();
    void spawnStar();

    void pauseGame();
    bool gameIsPaused();

    Player *getPlayer();

    /* Setter for referencial UI manipulation */
    void setPointLabel(QLabel *points);
    void setHealthBar(std::vector<QGraphicsEllipseItem *> *healthBar);
    void setReloadBar(QGraphicsRectItem *reloadBar);
    void setReloadText(QLabel *reloadText);
    void setMultiplicatorLabel(QLabel *multiplicatorLabel);
    void setPauseMenu(QGraphicsRectItem *pauseMenu, QLabel *pausedLabel, QLabel *backToStart);

public slots:
    void gameover();
    bool isGameOver();

signals:
    void valueChanged(bool value);

private:
    QGraphicsScene *scene_;
    QLabel *points_;
    QGraphicsRectItem *reloadBar_;
    QLabel *reloadText_;
    QLabel *multiplicatorLabel_;

    QGraphicsRectItem *pauseMenu_;
    QLabel *pausedLabel_;
    QLabel *backToStart_;

    QTimer *timer_;
    QTimer *scrapSpawner_;
    QTimer *asteroidSpawner_;
    QTimer *starsSpawner_;
    QTimer *cooldown_;

    SoundController *s_;

    Player *player_;

    int cooldownTimer_;

    bool gameIsPaused_;
    bool isOnCooldown_;
    bool gameIsOver_;
};
#endif // CONTROLLER_H
