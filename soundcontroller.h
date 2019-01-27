#ifndef SOUNDCONTROLLER_
#define SOUNDCONTROLLER_

#include <map>

#include <QString>
#include <QSoundEffect>
#include <QMediaPlaylist>
#include <QMediaPlayer>

class SoundController {
public:
    SoundController();

    void thrust();

    void intro();

private:
    std::map<QString, QSoundEffect*> sfx_;

    QSoundEffect *sfxThrust_;

    QMediaPlaylist *playlist_;

    QMediaPlayer *musicIntro_;
};

#endif // SOUNDCONTROLLER_
