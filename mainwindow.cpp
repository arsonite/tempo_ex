#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "star.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    this->setFixedSize(900, 700);
    ui_->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->view->resize(900, 700);
    ui_->view->setSceneRect(0, 0, 900, 700);
    ui_->view->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    /* StartView */
    QGraphicsScene *startView_ = new QGraphicsScene(this);

    QGraphicsScene *shopView_ = new QGraphicsScene(this);
    QGraphicsScene *infoView_ = new QGraphicsScene(this);
    QGraphicsScene *customizeView_ = new QGraphicsScene(this);
    QGraphicsScene *optionsView_ = new QGraphicsScene(this);

    /* GameView */
    QLabel *pointsLabel = new QLabel();
    QLabel *points = new QLabel();

    int id = QFontDatabase::addApplicationFont("qrc:/res/res/font/8-Bit Wonder.TTF");
    QString customFont = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont bit(customFont);
    bit.setWeight(20);

    pointsLabel->setText("Points: ");
    pointsLabel->setFont(bit);
    pointsLabel->move(350, 350);
    pointsLabel->resize(100, 100);

    gameView_->addWidget(pointsLabel);
    gameView_->addWidget(points);

    QGraphicsScene *gameView_ = new QGraphicsScene(this);
    gameController_ = new GameController(*gameView_, *points);
    gameView_->setBackgroundBrush(Qt::black);

    ui_->view->setScene(gameView_);
    //ui_->view->setScene(startView_);
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
            key == Qt::Key_D ||
            key == Qt::Key_Escape) {
        return true;
    }
    return false;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(assignedKey(e->key())) return
    gameController_->keyPressEvent(e);
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if(assignedKey(e->key())) return
    gameController_->keyReleaseEvent(e);
}

