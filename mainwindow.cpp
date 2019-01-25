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
    QString style = "QLabel { background-color : transparent; color : white; }";
    display_ = new QLabel();
    display_->move(-1540, -1750);
    display_->resize(4000, 4000);
    display_->setMovie(gif);
    display_->setStyleSheet(style);
    gif->start();
    startView_->addWidget(display_);

    infoLabel_ = new QGraphicsTextItem("Info");
    infoLabel_->setFont(bit);
    infoLabel_->setPos(375, -800);
    infoLabel_->setScale(2);
    infoLabel_->setZValue(10);
    startView_->addItem(infoLabel_);

    ui_->view->setScene(startView_);

    /* GameView */
    QLabel *pointsLabel = new QLabel();
    QLabel *points = new QLabel();

    pointsLabel->setFont(bit);
    pointsLabel->setText("Points");
    pointsLabel->move(395, 10);
    pointsLabel->resize(115, 20);
    pointsLabel->setAlignment(Qt::AlignCenter);
    pointsLabel->setStyleSheet(style);

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
    locks_ = new QMap<QString, bool>();
    locks_->insert("startView", false);
    locks_->insert("gameView", true);
    locks_->insert("infoView", true);
    locks_->insert("shopView", true);
    locks_->insert("customizeView", true);
    locks_->insert("optionsView", true);

    i_ = 0;
    counter_ = 0;
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
    if(!assignedKey(e->key())) return;
    if(!locks_->value("gameView")) gameController_->keyPressEvent(e);
    if(i_ != 0) return;

    lastKey_ = e->key();

    QTimer *ease = new QTimer();
    int interval = 16;
    ease->setInterval(interval);
    connect(ease, &QTimer::timeout, this, [=]() {
        navigate();
        counter_ += interval;

        if(counter_ >= TRANSITION_DURATION_) {
            i_ = 0;
            counter_ = 0;
            ease->stop();
        }
    });
    ease->start();
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if(assignedKey(e->key())) return;
    if(!locks_->value("gameView")) gameController_->keyPressEvent(e);
}

void MainWindow::navigate()
{

    if(lastKey_ == Qt::Key_W) {
    } else if(lastKey_ == Qt::Key_S) {
    } else if(lastKey_ == Qt::Key_D) {
    } else if(lastKey_ == Qt::Key_A) {
    }
}

void MainWindow::moveView()
{
    i_++;
    int i = i_ * (5 - i_); //Quadratic bezier curve
    switch(lastKey_) {
        case Qt::Key_W:
            display_->move(display_->x(), display_->y()-i);
            infoLabel_->setPos(infoLabel_->x(), infoLabel_->y()-i);
            break;
        case Qt::Key_S:
            display_->move(display_->x(), display_->y()+i);
            infoLabel_->setPos(infoLabel_->x(), infoLabel_->y()+i);
            break;
        case Qt::Key_D:
            display_->move(display_->x()+i, display_->y());
            break;
        case Qt::Key_A:
            display_->move(display_->x()-i, display_->y());
            break;
    }
}
