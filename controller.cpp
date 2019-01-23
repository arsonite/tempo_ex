#include "controller.h"
#include "projectile.h"
#include "scrap.h"
#include "asteroid.h"
#include "star.h"

#include <stdlib.h>

#include <QDebug>
#include <QMediaPlayer>
#include <QSoundEffect>

Controller::Controller(QGraphicsScene &scene) : scene_(&scene)
{
    player_ = new Player();
    player_->setPos(850/2, 610/2);
    scene_->addItem(player_);

    timer_ = new QTimer();
    timer_->setInterval((1000/60)*2); //Half of 60Hz - 16.7
    connect(timer_, &QTimer::timeout, this, [=](){
        /*
        QSoundEffect *sfx_thrust = new QSoundEffect();
        sfx_thrust->setSource(QUrl("qrc:/sfx/res/sfx/thrust.wav"));
        sfx_thrust->play();
        */

        player_->moveShip();
    });

    /*
    QMediaPlayer *music_game = new QMediaPlayer();
    music_game->setMedia(QUrl("qrc:/sfx/res/sfx/music_game.mp3"));
    music_game->play();
    */

    QTimer *scrapSpawner = new QTimer();
    scrapSpawner->setInterval(2500);
    connect(scrapSpawner, &QTimer::timeout, this, [=](){
        scene_->addItem(new Scrap());
    });
    scrapSpawner->start();

    QTimer *asteroidSpawner = new QTimer();
    asteroidSpawner->setInterval(5000);
    connect(scrapSpawner, &QTimer::timeout, this, [=](){
        scene_->addItem(new Asteroid());
    });
    asteroidSpawner->start();

    QGraphicsRectItem *stars = new QGraphicsRectItem();
    stars->setRect(0, 0, 900, 700);
    scene_->addItem(stars);
    QTimer *starsSpawner = new QTimer();
    starsSpawner->setInterval(50);
    connect(starsSpawner, &QTimer::timeout, this, [=](){
        new Star(*stars); // unnecessary computing
        // build probe if player is destroyed into here maybe?
    });
    starsSpawner->start();
}

Controller::~Controller()
{
    delete scene_;
}

void Controller::keyPressEvent(QKeyEvent *e)
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
        default:
            timer_->start();
            switchControl(e, true);
            break;
    }
}

void Controller::keyReleaseEvent(QKeyEvent *e)
{
    timer_->stop();
    switchControl(e, false);
}

void Controller::switchControl(QKeyEvent *e, bool b)
{
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

void Controller::shoot()
{
    /*
    QSoundEffect *sfx_shoot = new QSoundEffect();
    sfx_shoot->setSource(QUrl("qrc:/sfx/res/sfx/shoot.wav"));
    sfx_shoot->play();
    */

    Projectile *p = new Projectile(10, 25);
    p->setPos(player_->x(), player_->y());
    scene_->addItem(p);
    qDebug() << "Projectile fired. Number of Entities: " << scene_->items().size();
}

void Controller::useSpecial()
{
}

void Controller::superCharge()
{
}
