#ifndef SOUNDCONTROLLER_
#define SOUNDCONTROLLER_

#include <QString>
#include <QSoundEffect>
#include <QMediaPlayer>

class SoundController {
public:
    SoundController();

    void thrust();

    void intro();

private:
    QSoundEffect *sfxThrust_;

    QMediaPlayer *musicIntro_;
};

#endif // SOUNDCONTROLLER_
