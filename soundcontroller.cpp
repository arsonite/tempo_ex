#include <soundcontroller.h>

SoundController::SoundController()
{
    //sfxThrust_ = new QSoundEffect();
    //sfxThrust_->setSource(QUrl("qrc:/res/res/sfx/thrust.wav"));

    musicIntro_ = new QMediaPlayer();
    musicIntro_->setMedia(QUrl("qrc:/res/res/music/music_intro.mp3"));
}

void SoundController::thrust()
{
    if(sfxThrust_->isPlaying()) {
        return;
    }
    sfxThrust_->play();
}

void SoundController::intro()
{
    musicIntro_->play();
}
