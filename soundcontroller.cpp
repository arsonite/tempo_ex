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
    music_ = new std::map<QString, QString>();
    music_->insert(std::make_pair("intro", "qrc:/res/res/music/music_intro.mp3"));
    music_->insert(std::make_pair("game", "qrc:/res/res/music/music_game.mp3"));

    playlist_ = new QMediaPlaylist();
    playlist_->setPlaybackMode(QMediaPlaylist::Loop);

    musicPlayer_ = new QMediaPlayer();
    musicPlayer_->setPlaylist(playlist_);

}

void SoundController::playSFX(QString s)
{
    sfx_->at(s)->play();
}

void SoundController::playMusic(QString m)
{
    playlist_->clear();
    playlist_->addMedia(QUrl(music_->at(m)));
    musicPlayer_->play();
}
