#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamecontroller.h"

#include <map>

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

    bool assignedKey(int const key) const;

    void navigate();

private:
    Ui::MainWindow *ui_;

    QGraphicsScene *startView_;
    QLabel *display_;

    QGraphicsScene *shopView;
    QGraphicsScene *infoView;
    QGraphicsScene *customizeView_;
    QGraphicsScene *optionsView_;

    QGraphicsScene *gameView_;
    GameController *gameController_;
    //QGraphicsScene *winSceen_;
    //QGraphicsScene *lostScreen_;

    std::map<QString, bool> *locks_;

    int i_;
    int counter_;
    int lastKey_;

    const int TRANSITION_DURATION_ = 256;

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
};

#endif // MAINWINDOW_H
