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

    gameController_ = new GameController(gameView_, s);

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
    gameController_->setPointLabel(points);

    QLabel *reloadText = new QLabel();
    reloadText->setText("Reloading...");
    bit.setPointSize(18);
    reloadText->setFont(bit);
    reloadText->setStyleSheet("QLabel { background-color : transparent; color : #635EFE; }");
    reloadText->setVisible(false);
    reloadText->move(900/2-100, 700-155);
    gameView_->addWidget(reloadText);
    gameController_->setReloadText(reloadText);

    QGraphicsRectItem *reloadBar = new QGraphicsRectItem();
    reloadBar->setRect(900/2-200/2, 700-125, 0, 25);
    reloadBar->setBrush(QBrush(QColor(100, 100, 250)));
    reloadBar->setPen(QPen(Qt::NoPen));
    gameView_->addItem(reloadBar);
    gameController_->setReloadBar(reloadBar);

    QGraphicsRectItem *reloadBarFrame = new QGraphicsRectItem();
    reloadBarFrame->setRect(900/2-200/2, 700-125, 200, 25);
    reloadBarFrame->setPen(QPen(QColor(50, 50, 125)));
    gameView_->addItem(reloadBarFrame);

    QLabel *healthLabel = new QLabel();
    bit.setPointSize(14);
    healthLabel->setFont(bit);
    healthLabel->setText("Health");
    healthLabel->move(336, 620);
    healthLabel->resize(115, 14);
    healthLabel->setAlignment(Qt::AlignCenter);
    healthLabel->setStyleSheet("QLabel { background-color : transparent; color : #FFF; }");
    gameView_->addWidget(healthLabel);

    const int n = gameController_->getPlayer()->getMaxHealth();
    std::vector<QGraphicsEllipseItem*> *healthBar = new std::vector<QGraphicsEllipseItem*>();
    healthBar->reserve(n);
    for(int i = 0; i < n; i++) {
        QGraphicsEllipseItem *health = new QGraphicsEllipseItem();
        health->setRect(900/2-5 + (i * 19), 700-77, 10, 10);
        health->setBrush(QBrush(QColor(255, 75, 75)));
        health->setPen(QPen(Qt::NoPen));
        gameView_->addItem(health);
        healthBar->push_back(health);
    }
    gameController_->setHealthBar(healthBar);

    ui_->view->setScene(gameView_);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

bool MainWindow::assignedKey(int const key) const
{
    if(key == Qt::Key_C
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
