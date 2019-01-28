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

    void playSFX(QString s);
    void playMusic(QString m);

private:
    std::map<QString, QSoundEffect*> *sfx_;
    std::map<QString, QString*> *music_;

    QMediaPlayer *musicPlayer_;
    QMediaPlaylist *playlist_;
};

#endif // SOUNDCONTROLLER_
