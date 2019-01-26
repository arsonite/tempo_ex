#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "soundcontroller.h"

#include <ship.h>

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
    QString style = "QLabel { background-color : transparent; color : white; }";

    QMovie *gif = new QMovie(":/res/res/bg.gif");
    display_ = new QLabel();
    display_->move(-1540, -1750);
    display_->resize(4000, 4000);
    display_->setMovie(gif);
    display_->setStyleSheet(style);
    //gif->start();
    startView_->addWidget(display_);

    infoLabel_ = new QGraphicsTextItem("Info");
    infoLabel_->setFont(bit);
    infoLabel_->setPos(375, -800);
    infoLabel_->setScale(2);
    infoLabel_->setZValue(10);
    startView_->addItem(infoLabel_);

    /* Setting up locks */
    locks_ = new QMap<QString, bool>();
    locks_->insert("startView", false);
    locks_->insert("gameView", true);
    locks_->insert("infoView", false);
    locks_->insert("customizeView", false);
    locks_->insert("optionsView", false);
    locks_->insert("shopView", false);

    i_ = 0;
    counter_ = 0;

    //ui_->view->setScene(startView_);

    /* GameView */
    QGraphicsScene *gameView_ = new QGraphicsScene(this);
    gameView_->setBackgroundBrush(Qt::black);

    QLabel *pointsLabel = new QLabel();
    pointsLabel->setFont(bit);
    pointsLabel->setText("Points");
    pointsLabel->move(395, 10);
    pointsLabel->resize(115, 20);
    pointsLabel->setAlignment(Qt::AlignCenter);
    pointsLabel->setStyleSheet(style);
    gameView_->addWidget(pointsLabel);

    QLabel *points = new QLabel();
    points->setFont(bit);
    points->setText("0");
    points->move(395, 40);
    points->resize(115, 20);
    points->setAlignment(Qt::AlignCenter);
    points->setStyleSheet("QLabel { background-color : transparent; color : #00FF00; }");
    gameView_->addWidget(points);

    gameController_ = new GameController(*gameView_, *points, *s);

    QLabel *reloadText = new QLabel();
    points->setFont(bit);
    points->setStyleSheet("QLabel { background-color : transparent; color : #FF0000; }");

    QGraphicsRectItem *reloadBar = new QGraphicsRectItem();

    QGraphicsRectItem *reloadBarFrame = new QGraphicsRectItem();

    QLabel *healthLabel = new QLabel();

    QGraphicsEllipseItem *health = new QGraphicsEllipseItem();
    health->setRect(0, 0, 20, 20);
    health->setBrush(QBrush(Qt::))

    for(int i = 0; i < gameController_->getPlayer()->getMaxHealth(); i++) {

    }

    ui_->view->setScene(gameView_);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

bool MainWindow::assignedKey(int const key) const
{
    if(key == Qt::Key_B
            || key == Qt::Key_C
            || key == Qt::Key_Space
            || key == Qt::Key_W
            || key == Qt::Key_S
            || key == Qt::Key_A
            || key == Qt::Key_D
            || key == Qt::Key_Escape) {
        return true;
    }
    return false;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(!assignedKey(e->key()) || i_ != 0) {
        return;
    } else if(locks_->value("gameView")) {
        gameController_->keyPressEvent(e);
        return;
    }
    //lastKey_ = e->key();
    //navigate();
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if(!assignedKey(e->key())) {
        return;
    } else if(locks_->value("gameView")) {
        gameController_->keyReleaseEvent(e);
        return;
    }
}

void MainWindow::navigate()
{
    QTimer *ease = new QTimer();
    int interval = 16;
    ease->setInterval(interval);
    connect(ease, &QTimer::timeout, this, [=]() {
        i_++;
        int i = i_ * (5 - i_); //Quadratic bezier curve
        counter_ += interval;

        if(lastKey_ == Qt::Key_W) {
            if(!locks_->value("infoView")) moveToInfo(i);
        } else if(lastKey_ == Qt::Key_S) {

        } else if(lastKey_ == Qt::Key_D) {

        } else if(lastKey_ == Qt::Key_A) {

        }

        if(i_ == 0 || counter_ >= TRANSITION_DURATION_) {
            i_ = 0;
            counter_ = 0;
            ease->stop();
        }
    });
    ease->start();
}

void MainWindow::moveToStart(int i)
{
    display_->move(display_->x(), display_->y()+i);
    infoLabel_->setPos(infoLabel_->x(), infoLabel_->y()+i);
}

void MainWindow::moveToInfo(int i)
{
    if(display_->y() >= -934) {
        locks_->insert("infoView", true);
        locks_->insert("startView", false);
        i_ = 0;
        return;
    }

    display_->move(display_->x(), display_->y()-i);
    infoLabel_->setPos(infoLabel_->x(), infoLabel_->y()-i);
}

void MainWindow::moveToCustomize(int i)
{
}

void MainWindow::moveToOptions(int i)
{
}

void MainWindow::moveToShop(int i)
{
}
