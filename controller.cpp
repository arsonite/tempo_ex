#include "controller.h"
#include "projectile.h"
#include "asteroid.h"

#include <QDebug>
#include <QMediaPlayer>
#include <QSoundEffect>

Controller::Controller(QGraphicsScene &scene) : scene_(&scene)
{
    player_ = new Player();
    player_->setPos(850/2, 610/2);
    scene.addItem(player_);

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

    QTimer *spawner = new QTimer();
    spawner->setInterval(2500);
    connect(spawner, &QTimer::timeout, this, [=](){
        spawnAsteroid(0);
    });
    spawner->start();

    /*
    QTimer *stars_bg = new QTimer();
    stars_bg->setInterval(10);
    connect(stars_bg, &QTimer::timeout, this, [=](){
        spawnStars();
    });
    stars_bg->start();
    */
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

    Projectile *p = new Projectile();
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

void Controller::spawnAsteroid(int size)
{
    Asteroid *a = new Asteroid();
    scene_->addItem(a);
    qDebug() << "Number of Entities: " << scene_->items().size();
}

void Controller::spawnStars()
{
    Asteroid *a = new Asteroid();
    scene_->addItem(a);
    qDebug() << "Number of Entities: " << scene_->items().size();
}
