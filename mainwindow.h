/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamecontroller.h"
#include "clickableqlabel.h"

#include <QMap>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QKeyEvent>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

    void initializeStartView(QFont bit);
    void initializeGameView(QFont bit);
    void initializeLostView(QFont bit);

    bool assignedKey(int const key) const;

    void navigate();

    void moveToStart(int i);
    void moveToInfo(int i);
    void moveToCustomize(int i);

    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

public slots:
    void switchView();

private:
    Ui::MainWindow *ui_;

    SoundController *s_;

    QFont bit_;
    QString style_;

    QGraphicsScene *startView_;
    QMovie *gif_;
    QLabel *display_;
    ClickableQLabel *pressStartLabel_;
    QGraphicsTextItem *infoLabel_;
    QGraphicsTextItem *customizeLabel_;

    QGraphicsScene *gameView_;
    GameController *gameController_;

    QMap<QString, bool> *currentView_;

    int i_;
    int counter_;
    int lastKey_;

    const int TRANSITION_DURATION_ = 256;
};

#endif // MAINWINDOW_H
