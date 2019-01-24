#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "star.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    this->setFixedSize(900, 700);

    QGraphicsScene *startView_ = new QGraphicsScene(this);

    QGraphicsScene *shopView_ = new QGraphicsScene(this);
    QGraphicsScene *infoView_ = new QGraphicsScene(this);
    QGraphicsScene *customizeView_ = new QGraphicsScene(this);
    QGraphicsScene *optionsView_ = new QGraphicsScene(this);

    QGraphicsScene *gameView_ = new QGraphicsScene(this);
    //gameController_ = new GameController(*gameView_, *ui_->points);
    //gameView_->setBackgroundBrush(Qt::black);
    //ui_->view->setScene(gameView_);

    ui_->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->view->resize(900, 700);
    ui_->view->setSceneRect(0, 0, 900, 700);
    ui_->view->setAlignment(Qt::AlignTop | Qt::AlignLeft);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

bool MainWindow::assignedKey(int const key) const
{
    if(key == Qt::Key_B ||
            key == Qt::Key_C ||
            key == Qt::Key_Space ||
            key == Qt::Key_W ||
            key == Qt::Key_S ||
            key == Qt::Key_A ||
            key == Qt::Key_D) {
        return true;
    }
    return false;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(assignedKey(e->key())) return
    controller_->keyPressEvent(e);
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if(assignedKey(e->key())) return
    controller_->keyReleaseEvent(e);
}

