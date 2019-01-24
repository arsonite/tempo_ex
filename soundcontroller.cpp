#include <soundcontroller.h>

SoundController::SoundController()
{
    sfx_trust_ = new QSoundEffect();
    //sfx_trust_->setSource(QUrl("qrc:/res/res/sfx/thrust.wav"));
}

void SoundController::thrust()
{
    if(sfx_trust_->isPlaying()) {
        return;
    }
    sfx_trust_->play();
}
