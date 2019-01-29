/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#include "gamecontroller.h"
#include "projectile.h"
#include "scrap.h"
#include "asteroid.h"
#include "star.h"
#include "ship.h"

#include <stdlib.h>

#include <QDebug>

GameController::GameController(QGraphicsScene *scene, SoundController *s): scene_(scene), s_(s)
{
    player_ = new Player(1, 1, -2); //z-index: -2
    player_->setPos(900/2-player_->getShip()->getHitbox().y()/2, 700/2);
    scene_->addItem(player_);

    connect(player_, &Player::valueChanged, this, &GameController::gameover);

    /* Timer for player move animation */
    timer_ = new QTimer();
    timer_->setInterval((1000/60)*2); //Half of 60Hz - 16.7

    connect(timer_, &QTimer::timeout, this, [=](){
        player_->moveShip();
    });

    /* Spawner for scrapmetal */
    scrapSpawner_ = new QTimer();
    scrapSpawner_->setInterval(2500);
    connect(scrapSpawner_, &QTimer::timeout, this, [=](){
        scene_->addItem(new Scrap(-2, gameIsPaused_)); //z-index: -2
    });
    scrapSpawner_->start();

    /* Spawner for normal and golden asteroids */
    asteroidSpawner_ = new QTimer();
    asteroidSpawner_->setInterval(3500);
    connect(asteroidSpawner_, &QTimer::timeout, this, [=](){
        scene_->addItem(new Asteroid(-2, gameIsPaused_)); //z-index: -2
    });
    asteroidSpawner_->start();

    /* Spawner for background stars */
    starsSpawner_ = new QTimer();
    starsSpawner_->setInterval(50);
    connect(starsSpawner_, &QTimer::timeout, this, [=](){
        spawnStar();
    });
    starsSpawner_->start();

    /* Weapon cooldown timer */
    int interval = 100;
    cooldownTimer_ = 0;
    cooldown_ = new QTimer();
    cooldown_->setInterval(interval);
    connect(cooldown_, &QTimer::timeout, this, [=](){
        int maxValue = player_->getShip()->getWeapons()[0]->getReloadTime();
        if(cooldownTimer_ >= maxValue) {
            reloadText_->setVisible(false);
            cooldownTimer_ = 0;
            cooldown_->stop();
            isOnCooldown_ = false;
        }
        double perc = 200 * ((cooldownTimer_ * 100.0 / maxValue) / 100.0);
        reloadBar_->setRect(900/2-200/2, 700-125, perc, 25);
        cooldownTimer_+= interval;
    });

    gameIsPaused_ = false;
    isOnCooldown_ = false;
    gameIsOver_ = false;
}

GameController::~GameController()
{
    delete scene_;
}

void GameController::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())  {
        case Qt::Key_Space:
            shoot();
            break;
        case Qt::Key_Escape:
            pauseGame();
            break;
        default:
            switchControl(e, true);
            break;
    }
}

void GameController::keyReleaseEvent(QKeyEvent *e)
{
    if(gameIsPaused_) return;
    timer_->stop();
    switchControl(e, false);
}

void GameController::switchControl(QKeyEvent *e, bool b)
{
    if(gameIsPaused_) return;
    if(timer_->isActive()) timer_->stop();
    timer_->start();

    switch(e->key())  {
        case Qt::Key_W:
            player_->keyPress(0, b);
            break;
        case Qt::Key_S:
            player_->keyPress(1, b);
            break;
        case Qt::Key_A:
            player_->keyPress(2, b);
            break;
        case Qt::Key_D:
            player_->keyPress(3, b);
            break;
        default: break;
    }
}

void GameController::shoot()
{
    if(gameIsPaused_ || isOnCooldown_) return;
    cooldown_->start();
    reloadText_->setVisible(true);
    isOnCooldown_ = true;

    std::vector<Weapon*> weapons = player_->getShip()->getWeapons();
    for(int i = 0; i < weapons.size(); i++) {
        int c = 0;
        int n = 1;
        if(weapons[0]->getClass() == 2) n = 5;
        while(c < n) {
            Projectile *p = new Projectile(-2, c * 5, gameIsPaused_, weapons[i]); //z-index: -2
            QRectF rect = weapons[i]->rect();
            p->setPos(player_->pos().x(), player_->pos().y());
            p->setRect(rect.x()-rect.width()/2-5/2, rect.y()-rect.height(), 15, 15);
            scene_->addItem(p);
            c++;
        }
    }

    switch(weapons[0]->getClass()) {
        case 1:
            s_->playSFX("machineGun");
            break;
        case 2:
            s_->playSFX("shotgun");
            break;
        case 3:
            s_->playSFX("cannon");
            break;
    }
}

void GameController::spawnStar()
{
    int p = player_->getPoints();
    scene_->addItem(new Star(-3, gameIsPaused_));  //z-index: -3
    points_->setNum(p);
}

void GameController::pauseGame()
{
    gameIsPaused_ = !gameIsPaused_;
    if(gameIsPaused_) {
        timer_->stop();
        scrapSpawner_->stop();
        asteroidSpawner_->stop();
        starsSpawner_->stop();
        cooldown_->stop();
        pauseMenu_->setVisible(true);
        pausedLabel_->setVisible(true);
        backToStart_->setVisible(true);
        return;
    }
    scrapSpawner_->start();
    asteroidSpawner_->start();
    starsSpawner_->start();
    pauseMenu_->setVisible(false);
    pausedLabel_->setVisible(false);
    backToStart_->setVisible(false);
    if(isOnCooldown_) cooldown_->start();
}

bool GameController::gameIsPaused()
{
    return gameIsPaused_;
}

Player* GameController::getPlayer()
{
    return player_;
}

void GameController::setPointLabel(QLabel *points)
{
    points_ = points;
}

void GameController::setHealthBar(std::vector<QGraphicsEllipseItem*> *healthBar)
{
    player_->setHealthBar(healthBar);
}

void GameController::setReloadBar(QGraphicsRectItem *reloadBar)
{
    reloadBar_ = reloadBar;
}

void GameController::setReloadText(QLabel *reloadText)
{
    reloadText_ = reloadText;
}

void GameController::setMultiplicatorLabel(QLabel *multiplicatorLabel)
{
    multiplicatorLabel_ = multiplicatorLabel;
    player_->setMultiplicatorLabel(multiplicatorLabel_);
}

void GameController::setPauseMenu(QGraphicsRectItem *pauseMenu, QLabel *pausedLabel, QLabel *backToStart)
{
    pauseMenu_ = pauseMenu;
    pausedLabel_ = pausedLabel;
    backToStart_ = backToStart;
}

void GameController::gameover()
{
    gameIsOver_ = true;
    emit valueChanged(gameIsOver_);
}

bool GameController::isGameOver()
{
    return gameIsOver_;
}
