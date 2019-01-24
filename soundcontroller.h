#ifndef SOUNDCONTROLLER_
#define SOUNDCONTROLLER_

#include <QString>
#include <QSoundEffect>
#include <QMediaPlayer>

class SoundController {
public:
    SoundController();

    void thrust();

private:
    QSoundEffect *sfx_trust_;
};

#endif // SOUNDCONTROLLER_
