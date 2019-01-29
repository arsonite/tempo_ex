#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamecontroller.h"
#include "clickableqlabel.h"

#include <QMap>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

    void retrieveStartView(QFont bit, QString style, QMovie *gif, SoundController *s);
    void retrieveGameView(QFont bit, QString style, QMovie *gif, SoundController *s);

    bool assignedKey(int const key) const;

    void navigate();

    void moveToStart(int i);
    void moveToInfo(int i);
    void moveToCustomize(int i);
    void moveToOptions(int i);
    void moveToShop(int i);

    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

private:
    Ui::MainWindow *ui_;

    QGraphicsScene *startView_;
    QLabel *display_;
    ClickableQLabel *pressStartLabel_;

    QGraphicsTextItem *infoLabel_;
    QGraphicsTextItem *customizeLabel_;
    QGraphicsTextItem *optionsLabel_;
    QGraphicsTextItem *shopLabel_;

    QGraphicsScene *gameView_;
    GameController *gameController_;

    QMap<QString, bool> *currentView_;

    int i_;
    int counter_;
    int lastKey_;

    const int TRANSITION_DURATION_ = 256;

protected:

};

#endif // MAINWINDOW_H
