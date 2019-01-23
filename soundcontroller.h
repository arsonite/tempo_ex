#ifndef SOUNDCONTROLLER_
#define SOUNDCONTROLLER_

#include <QString>
#include <QMap>

#include <QSoundEffect>
#include <QMediaPlayer>

class SoundController {
public:
    typedef QMap<QString, QSoundEffect> sfx;
    static sfx fillSFXMap();
};

#endif // SOUNDCONTROLLER_
