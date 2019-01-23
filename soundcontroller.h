#ifndef SOUNDCONTROLLER_
#define SOUNDCONTROLLER_

#include <string>
#include <map>

#include <QSoundEffect>
#include <QMediaPlayer>

class SoundController
{
public:
    static void init();

    static void playSFX(std::string s);
    static void playMusic(std::string m);

private:
    static std::map<std::string, QSoundEffect> sfx;
    static std::map<std::string, QMediaPlayer> music;
};

#endif // SOUNDCONTROLLER_
