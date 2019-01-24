#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "soundcontroller.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFontDatabase>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    SoundController *s = new SoundController();
    s->intro();

    ui_->setupUi(this);
    this->setFixedSize(900, 700);
    ui_->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->view->resize(900, 700);
    ui_->view->setSceneRect(0, 0, 900, 700);
    ui_->view->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    /* Loading custom 8-Bit font */
    int id = QFontDatabase::addApplicationFont(":/res/res/8-Bit Wonder.TTF");
    qDebug() << id;
    QString customFont = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont bit(customFont);
    bit.setPointSize(20);

    /* StartView */
    QGraphicsScene *startView_ = new QGraphicsScene(this);

    QMovie *gif = new QMovie(":/res/res/bg.gif");
    QLabel *display = new QLabel();
    display->move(-1540, -1750);
    display->resize(4000, 4000);
    display->setMovie(gif);
    display->setStyleSheet("QLabel { background-color : transparent; }");

    gif->start();

    startView_->addWidget(display);

    //startView_->setBackgroundBrush(Qt::black);

    ui_->view->setScene(startView_);

    /* ShopView */
    QGraphicsScene *shopView_ = new QGraphicsScene(this);

    /* InfoView */
    QGraphicsScene *infoView_ = new QGraphicsScene(this);

    /* CustomizeView */
    QGraphicsScene *customizeView_ = new QGraphicsScene(this);

    /* OptionsView */
    QGraphicsScene *optionsView_ = new QGraphicsScene(this);

    /* GameView */
    QLabel *pointsLabel = new QLabel();
    QLabel *points = new QLabel();

    pointsLabel->setFont(bit);
    pointsLabel->setText("Points");
    pointsLabel->move(395, 10);
    pointsLabel->resize(115, 20);
    pointsLabel->setAlignment(Qt::AlignCenter);
    pointsLabel->setStyleSheet("QLabel { background-color : transparent; color : white; }");

    points->setFont(bit);
    points->setText("0");
    points->move(395, 40);
    points->resize(115, 20);
    points->setAlignment(Qt::AlignCenter);
    points->setStyleSheet("QLabel { background-color : transparent; color : #00FF00; }");

    QGraphicsScene *gameView_ = new QGraphicsScene(this);
    gameView_->addWidget(pointsLabel);
    gameView_->addWidget(points);

    //gameController_ = new GameController(*gameView_, *points, *s);
    gameView_->setBackgroundBrush(Qt::black);

    /* Setting locks */
    locks_ = {false, true, true, true, true, true, true, true};
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

