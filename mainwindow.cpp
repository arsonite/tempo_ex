/** DISCLAIMER
 * Beuth-Hochschule
 * Effiziente Software entwickeln mit C++
 * Aufgabe 3
 * Burak Günaydin (2019)
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "soundcontroller.h"
#include "ship.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFontDatabase>
#include <QMovie>

/**
 * Main and only view.
 *
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui_(new Ui::MainWindow)
{
    s_ = new SoundController();

    ui_->setupUi(this);
    this->setFixedSize(900, 700);
    ui_->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui_->view->resize(900, 700);
    ui_->view->setSceneRect(0, 0, 900, 700);
    ui_->view->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    setWindowTitle("Tempo EX");

    /* Loading custom 8-Bit font */
    int id = QFontDatabase::addApplicationFont(":/res/res/8-Bit Wonder.TTF");
    QString customFont = QFontDatabase::applicationFontFamilies(id).at(0);
    bit_.setFamily(customFont);
    bit_.setPointSize(20);

    style_ = "QLabel { background-color : transparent; color : white; }";

    /* Setting up locks */
    currentView_ = new QMap<QString, bool>();
    currentView_->insert("startView", false);
    currentView_->insert("gameView", true);
    currentView_->insert("infoView", false);
    currentView_->insert("customizeView", false);
    currentView_->insert("lostView", false);

    i_ = 0;
    counter_ = 0;

    switchView();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

/**
 * Switches and initializes inbetween the views.
 * Performance is almost the same as just saving the objects and switching the scenes.
 * Other than that, allows to avoid spaghetti code.
 *
 * @brief MainWindow::switchView
 */
void MainWindow::switchView()
{
    if (currentView_->value("gameView"))
    {
        if (gameController_->isGameOver())
        {
            initializeLostView(bit_);
            return;
        }
        initializeStartView(bit_);
    }
    else if (currentView_->value("startView") || currentView_->value("lostView"))
    {
        initializeGameView(bit_);
    }
}

void MainWindow::initializeStartView(QFont bit)
{
    s_->playMusic("intro");

    gif_ = new QMovie(":/res/res/bg.gif");
    display_ = new QLabel();
    display_->move(-1555, -1750);
    display_->resize(4000, 4000);
    display_->setMovie(gif_);
    display_->setStyleSheet(style_);
    gif_->start();
    //gif_->stop(); //Disabled due to lag

    currentView_->insert("startView", true);
    currentView_->insert("gameView", false);
    currentView_->insert("lostView", false);

    startView_ = new QGraphicsScene(this);
    startView_->addWidget(display_);

    infoLabel_ = new QGraphicsTextItem("Info");
    infoLabel_->setFont(bit);
    infoLabel_->setPos(-440, 20);
    infoLabel_->setScale(2);
    infoLabel_->setZValue(10);
    startView_->addItem(infoLabel_);

    pressStartLabel_ = new ClickableQLabel();
    bit.setPointSize(30);
    pressStartLabel_->setFont(bit);
    pressStartLabel_->setText("> Press to Start <");
    pressStartLabel_->move(900 / 2 - 500 / 2, 350);
    pressStartLabel_->resize(500, 40);
    pressStartLabel_->setAlignment(Qt::AlignCenter);
    pressStartLabel_->setStyleSheet(style_);
    connect(pressStartLabel_, &ClickableQLabel::clicked, this, &MainWindow::switchView);
    startView_->addWidget(pressStartLabel_);

    ui_->view->setScene(startView_);
}

void MainWindow::initializeGameView(QFont bit)
{
    gif_->stop();

    s_->playMusic("game");

    currentView_->insert("startView", false);
    currentView_->insert("gameView", true);
    currentView_->insert("lostView", false);

    gameView_ = new QGraphicsScene(this);
    gameView_->setBackgroundBrush(Qt::black);

    gameController_ = new GameController(gameView_, s_);
    connect(gameController_, &GameController::valueChanged, this, &MainWindow::switchView);

    QLabel *pointsLabel = new QLabel();
    pointsLabel->setFont(bit);
    pointsLabel->setText("Points");
    pointsLabel->move(900 / 2 - 115 / 2, 10);
    pointsLabel->resize(115, 20);
    pointsLabel->setAlignment(Qt::AlignCenter);
    pointsLabel->setStyleSheet(style_);
    gameView_->addWidget(pointsLabel);

    QLabel *points = new QLabel();
    points->setFont(bit);
    points->setText("0");
    points->move(900 / 2 - 115 / 2, 40);
    points->resize(115, 20);
    points->setAlignment(Qt::AlignCenter);
    points->setStyleSheet("QLabel { background-color : transparent; color : #00FF00; }");
    gameView_->addWidget(points);
    gameController_->setPointLabel(points);

    QLabel *multiplicator = new QLabel();
    multiplicator->setFont(bit);
    multiplicator->move(275, 10);
    multiplicator->resize(115, 20);
    multiplicator->setAlignment(Qt::AlignRight);
    multiplicator->setStyleSheet("QLabel { background-color : transparent; color : #00FF00; }");
    multiplicator->setVisible(false);
    gameView_->addWidget(multiplicator);
    gameController_->setMultiplicatorLabel(multiplicator);

    QLabel *reloadText = new QLabel();
    reloadText->setText("Reloading...");
    bit.setPointSize(18);
    reloadText->setFont(bit);
    reloadText->setStyleSheet("QLabel { background-color : transparent; color : #635EFE; }");
    reloadText->setVisible(false);
    reloadText->move(900 / 2 - 100, 700 - 155);
    gameView_->addWidget(reloadText);
    gameController_->setReloadText(reloadText);

    QGraphicsRectItem *reloadBar = new QGraphicsRectItem();
    reloadBar->setRect(900 / 2 - 200 / 2, 700 - 125, 0, 25);
    reloadBar->setBrush(QBrush(QColor(100, 100, 250)));
    reloadBar->setPen(QPen(Qt::NoPen));
    gameView_->addItem(reloadBar);
    gameController_->setReloadBar(reloadBar);

    QGraphicsRectItem *reloadBarFrame = new QGraphicsRectItem();
    reloadBarFrame->setRect(900 / 2 - 200 / 2, 700 - 125, 200, 25);
    reloadBarFrame->setPen(QPen(QColor(50, 50, 125)));
    gameView_->addItem(reloadBarFrame);

    QLabel *healthLabel = new QLabel();
    bit.setPointSize(14);
    healthLabel->setFont(bit);
    healthLabel->setText("Health");
    healthLabel->move(336, 620);
    healthLabel->resize(115, 14);
    healthLabel->setAlignment(Qt::AlignCenter);
    healthLabel->setStyleSheet(style_);
    gameView_->addWidget(healthLabel);

    const int n = gameController_->getPlayer()->getMaxHealth();
    std::vector<QGraphicsEllipseItem *> *healthBar = new std::vector<QGraphicsEllipseItem *>();
    healthBar->reserve(n);
    for (int i = 0; i < n; i++)
    {
        QGraphicsEllipseItem *health = new QGraphicsEllipseItem();
        health->setRect(900 / 2 - 5 + (i * 19), 700 - 77, 10, 10);
        health->setBrush(QBrush(QColor(255, 75, 75)));
        health->setPen(QPen(Qt::NoPen));
        gameView_->addItem(health);
        healthBar->push_back(health);
    }
    gameController_->setHealthBar(healthBar);

    QGraphicsRectItem *pauseMenu = new QGraphicsRectItem();
    pauseMenu->setZValue(0);
    pauseMenu->setRect(0, 0, 900, 700);
    pauseMenu->setBrush(QColor(0, 0, 0));
    pauseMenu->setPen(QPen(Qt::NoPen));
    pauseMenu->setOpacity(0.65);
    pauseMenu->setVisible(false);
    gameView_->addItem(pauseMenu);

    QLabel *pausedLabel = new QLabel();
    bit.setPointSize(40);
    pausedLabel->setFont(bit);
    pausedLabel->setText("Paused");
    pausedLabel->move(900 / 2 - 250 / 2, 100);
    pausedLabel->resize(250, 40);
    pausedLabel->setAlignment(Qt::AlignCenter);
    pausedLabel->setStyleSheet("QLabel { background-color : transparent; color : #FFF; }");
    pausedLabel->setVisible(false);
    gameView_->addWidget(pausedLabel);

    ClickableQLabel *backToStart = new ClickableQLabel();
    bit.setPointSize(30);
    backToStart->setFont(bit);
    backToStart->setText("> Back to Home <");
    backToStart->move(900 / 2 - 400 / 2, 300);
    backToStart->resize(400, 40);
    backToStart->setAlignment(Qt::AlignCenter);
    backToStart->setStyleSheet("QLabel { background-color : transparent; color : #FFF; }");
    backToStart->setVisible(false);
    connect(backToStart, &ClickableQLabel::clicked, this, &MainWindow::switchView);
    gameView_->addWidget(backToStart);

    gameController_->setPauseMenu(pauseMenu, pausedLabel, backToStart);

    ui_->view->setScene(gameView_);
}

void MainWindow::initializeLostView(QFont bit)
{
    s_->playSFX("lost");
    s_->playMusic("lost");

    currentView_->insert("lostView", true);
    currentView_->insert("gameView", false);

    QGraphicsScene *lostView_ = new QGraphicsScene(this);
    lostView_->setBackgroundBrush(Qt::black);

    QLabel *gameoverLabel = new QLabel();
    bit.setPointSize(40);
    gameoverLabel->setFont(bit);
    gameoverLabel->setText("Gameover");
    gameoverLabel->move(900 / 2 - 400 / 2, 100);
    gameoverLabel->resize(400, 40);
    gameoverLabel->setAlignment(Qt::AlignCenter);
    gameoverLabel->setStyleSheet("QLabel { background-color : transparent; color : #FFF; }");
    lostView_->addWidget(gameoverLabel);

    ClickableQLabel *restartGame = new ClickableQLabel();
    bit.setPointSize(30);
    restartGame->setFont(bit);
    restartGame->setText("> Restart <");
    restartGame->move(900 / 2 - 300 / 2, 300);
    restartGame->resize(300, 40);
    restartGame->setAlignment(Qt::AlignCenter);
    restartGame->setStyleSheet("QLabel { background-color : transparent; color : #FFF; }");
    connect(restartGame, &ClickableQLabel::clicked, this, &MainWindow::switchView);
    lostView_->addWidget(restartGame);

    ui_->view->setScene(lostView_);
}

bool MainWindow::assignedKey(int const key) const
{
    if (key == Qt::Key_Space || key == Qt::Key_W || key == Qt::Key_S || key == Qt::Key_A || key == Qt::Key_D || key == Qt::Key_Escape)
    {
        return true;
    }
    return false;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    /* Prevents unknown keys to be pressed and in the middle of transitions or if you're in the lost screen */
    if (!assignedKey(e->key()) || i_ != 0 || currentView_->value("lostView"))
    {
        return;
    }
    else if (currentView_->value("gameView"))
    {
        gameController_->keyPressEvent(e);
        return;
    }
    lastKey_ = e->key(); //Saves the last key pressed
    navigate();
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if (!assignedKey(e->key()))
    {
        return;
    }
    else if (currentView_->value("gameView"))
    {
        gameController_->keyReleaseEvent(e);
    }
}

void MainWindow::navigate()
{
    if (lastKey_ == Qt::Key_W || lastKey_ == Qt::Key_S || lastKey_ == Qt::Key_Space)
        return;
    QTimer *ease = new QTimer();
    int interval = 16;
    ease->setInterval(interval);
    connect(ease, &QTimer::timeout, this, [=]() {
        i_++;
        int i = i_ * (5 - i_); //Cubic bezier curve for smooth transition
        counter_ += interval;

        /* Stops the timer after reaching the maximum transition allowance */
        if (counter_ >= TRANSITION_DURATION_)
        {
            i_ = 0;
            counter_ = 0;
            ease->stop();
        }

        if (lastKey_ == Qt::Key_A)
        {
            if (currentView_->value("startView"))
            {
                moveToInfo(i);
            }
            else if (currentView_->value("customizeView"))
            {
                moveToStart(i);
            }
        }
        else if (lastKey_ == Qt::Key_D)
        {
            if (currentView_->value("infoView"))
            {
                moveToStart(i);
            }
            else if (currentView_->value("startView"))
            {
                moveToCustomize(i);
            }
        }
    });
    ease->start();
}

void MainWindow::moveToStart(int i)
{
    if (i_ == 0)
    {
        currentView_->insert("startView", true);
        currentView_->insert("infoView", false);
        currentView_->insert("customizeView", false);
    }

    display_->move(display_->x() + i, display_->y());
    pressStartLabel_->move(pressStartLabel_->x() + i, pressStartLabel_->y());

    infoLabel_->setPos(infoLabel_->x() + i, infoLabel_->y());
}

void MainWindow::moveToInfo(int i)
{
    if (i_ == 0)
    {
        currentView_->insert("infoView", true);
        currentView_->insert("startView", false);
    }

    display_->move(display_->x() - i, display_->y());
    pressStartLabel_->move(pressStartLabel_->x() - i, pressStartLabel_->y());

    infoLabel_->setPos(infoLabel_->x() - i, infoLabel_->y());
}

void MainWindow::moveToCustomize(int i)
{
    if (i_ == 0)
    {
        currentView_->insert("customizeView", true);
        currentView_->insert("startView", false);
    }

    display_->move(display_->x() + i, display_->y());
    pressStartLabel_->move(pressStartLabel_->x() + i, pressStartLabel_->y());
}
