#include "soundcontroller.h"

void SoundController::init()
{
    QSoundEffect *thrust = new QSoundEffect();
    thrust->setSource(QUrl("qrc:/res/res/sfx/thrust.wav"));
    sfx.insert(std::make_pair("thrust" , thrust));

    QMediaPlayer *music_game = new QMediaPlayer();
}

void SoundController::playSFX(std::string s)
{
    sfx.at(s).play();
}

void SoundController::playMusic(std::string m)
{

}
