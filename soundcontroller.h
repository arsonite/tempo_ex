/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#ifndef SOUNDCONTROLLER_
#define SOUNDCONTROLLER_

#include <map>

#include <QString>
#include <QSoundEffect>
#include <QMediaPlaylist>
#include <QMediaPlayer>

class SoundController: public QObject {
Q_OBJECT
public:
    SoundController();

    void playSFX(QString s);
    void playMusic(QString m);

public slots:
    void playerGetsDamaged();
    void playerCollects();

private:
    std::map<QString, QSoundEffect*> *sfx_;
    std::map<QString, QString> *music_;

    QMediaPlayer *musicPlayer_;
    QMediaPlaylist *playlist_;
};

#endif // SOUNDCONTROLLER_
