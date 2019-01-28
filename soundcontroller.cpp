#include <soundcontroller.h>

#include <QSound>

SoundController::SoundController()
{
    sfx_ = new std::map<QString, QSoundEffect*>();

    /* Initiliazing all sfx */
    QSoundEffect *sfxMachineGun = new QSoundEffect();
    sfxMachineGun->setSource(QUrl("qrc:/res/res/sfx/machine_gun.wav"));
    sfx_->insert(std::make_pair("machineGun", sfxMachineGun));

    QSoundEffect *sfxShotgun = new QSoundEffect();
    sfxShotgun->setSource(QUrl("qrc:/res/res/sfx/shotgun.wav"));
    sfx_->insert(std::make_pair("shotgun", sfxShotgun));

    QSoundEffect *sfxCannon = new QSoundEffect();
    sfxCannon->setSource(QUrl("qrc:/res/res/sfx/cannon.wav"));
    sfx_->insert(std::make_pair("cannon", sfxCannon));

    /* Initiliazing music player and playlist for looping purposes */
    musicPlayer_ = new QMediaPlayer();
    musicPlayer_->setMedia(QUrl("qrc:/res/res/music/music_game.mp3"));

    playlist_ = new QMediaPlaylist();
}

void SoundController::playSFX(QString s)
{
    sfx_->at(s)->play();
}

void SoundController::playMusic(QString m)
{
    playlist_->clear();
    playlist_->addMedia(QUrl("qrc:/res/res/music/music_game.mp3"));
    musicPlayer_->setPlaylist(playlist_);
    musicPlayer_->play();
}
