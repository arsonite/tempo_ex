#include <soundcontroller.h>

SoundController::SoundController()
{
    //sfxThrust_ = new QSoundEffect();
    //sfxThrust_->setSource(QUrl("qrc:/res/res/sfx/thrust.wav"));

    sfx_ = std::map<QString, QSoundEffect*>();

    musicIntro_ = new QMediaPlayer();
    musicIntro_->setMedia(QUrl("qrc:/res/res/music/music_intro.mp3"));

    playlist_ = new QMediaPlaylist();
    playlist_ ->setPlaybackMode(QMediaPlaylist::Loop);
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
    playlist_->clear();
    playlist_->addMedia(QUrl(musicIntro_->currentMedia().canonicalUrl().toString()));
    musicIntro_->setPlaylist(playlist_);
    musicIntro_->play();
}
