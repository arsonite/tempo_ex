#include "gamecontroller.h"
#include "soundcontroller.h"
#include "projectile.h"
#include "scrap.h"
#include "asteroid.h"
#include "star.h"

#include <stdlib.h>

#include <QDebug>

GameController::GameController(QGraphicsScene &scene, QLabel &points) : scene_(&scene), points_(&points)
{
    SoundController *s = new SoundController();

    player_ = new Player(-2); //z-index: -2
    player_->setPos(850/2, 610/2);
    scene_->addItem(player_);

    timer_ = new QTimer();
    timer_->setInterval((1000/60)*2); //Half of 60Hz - 16.7
    connect(timer_, &QTimer::timeout, this, [=](){
        //s->playSFX("thrust");
        player_->moveShip();
    });

    scrapSpawner_ = new QTimer();
    scrapSpawner_->setInterval(2500);
    connect(scrapSpawner_, &QTimer::timeout, this, [=](){
        scene_->addItem(new Scrap(-2)); //z-index: -2
    });
    scrapSpawner_->start();

    asteroidSpawner_ = new QTimer();
    asteroidSpawner_->setInterval(5000);
    connect(asteroidSpawner_, &QTimer::timeout, this, [=](){
        scene_->addItem(new Asteroid(-2)); //z-index: -2
    });
    asteroidSpawner_->start();

    starsSpawner_ = new QTimer();
    starsSpawner_->setInterval(50);
    connect(starsSpawner_, &QTimer::timeout, this, [=](){
        spawnStar();
    });
    starsSpawner_->start();

    gameIsPaused_ = false;
}

GameController::~GameController()
{
    delete scene_;
}

void GameController::keyPressEvent(QKeyEvent *e)
{
    qDebug() << "keyPressEvent()";
    switch(e->key())  {
        case Qt::Key_Space:
            shoot();
            break;
        case Qt::Key_B:
            useSpecial();
            break;
        case Qt::Key_C:
            superCharge();
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
    timer_->stop();
    switchControl(e, false);
}

void GameController::switchControl(QKeyEvent *e, bool b)
{
    if(gameIsPaused_) return;

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
    QSoundEffect *sfx_shoot = new QSoundEffect();
    sfx_shoot->setSource(QUrl("qrc:/sfx/res/sfx/shoot.wav"));
    sfx_shoot->play();

    Projectile *p = new Projectile(0, 10, 25, this);
    p->setPos(player_->x(), player_->y());
    scene_->addItem(p);
    qDebug() << "Projectile fired. Number of Entities: " << scene_->items().size();
}

void GameController::useSpecial()
{
}

void GameController::superCharge()
{
}

void GameController::spawnStar()
{
    int p = player_->getPoints();
    scene_->addItem(new Star(-3));  //z-index: -3
    points_->setNum(p);
    if(p < 0) {
        //gameover_ = true;
    }
}

void GameController::pauseGame()
{
    gameIsPaused_ = !gameIsPaused_;
    if(gameIsPaused_) {
        timer_->stop();
        scrapSpawner_->stop();
        asteroidSpawner_->stop();
        starsSpawner_->stop();
        return;
    }
    scrapSpawner_->start();
    asteroidSpawner_->start();
    starsSpawner_->start();
}

bool GameController::gameIsPaused()
{
    return gameIsPaused_;
}
