#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamecontroller.h"

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

private:
    Ui::MainWindow *ui_;

    QGraphicsScene *startView_;

    QGraphicsScene *shopView;
    QGraphicsScene *infoView;
    QGraphicsScene *customizeView_;
    QGraphicsScene *optionsView_;

    QGraphicsScene *gameView_;
    //QGraphicsScene *winSceen_;
    //QGraphicsScene *lostScreen_;

    GameController *gameController_;

protected:
  void keyPressEvent(QKeyEvent *e) override;
  void keyReleaseEvent(QKeyEvent *e) override;
};

#endif // MAINWINDOW_H
