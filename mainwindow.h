#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamecontroller.h"

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

    bool assignedKey(int const key) const;

    void navigate();
    void moveView();

private:
    Ui::MainWindow *ui_;

    QGraphicsScene *startView_;
    QLabel *display_;
    QGraphicsTextItem *infoLabel_;
    QGraphicsTextItem *customizeLabel_;
    QGraphicsTextItem *optionsLabel_;
    QGraphicsTextItem *shopLabel_;

    QGraphicsScene *gameView_;
    GameController *gameController_;
    //QGraphicsScene *winSceen_;
    //QGraphicsScene *lostScreen_;

    QMap<QString, bool> *locks_;

    int i_;
    int counter_;
    int lastKey_;

    const int TRANSITION_DURATION_ = 256;

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
};

#endif // MAINWINDOW_H
