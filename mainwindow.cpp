#include "mainwindow.h"
#include "game.h"

#include <QFont>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>

void MainWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap background(":/images/background1.jpg");
    painter.drawPixmap(rect(), background);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Главное меню");
    resize(700, 500);

    QWidget *centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setAlignment(Qt::AlignCenter);

    setWindowIcon(QIcon(":/images/icon.png"));

    titleLabel = new QLabel("Космос️");
    titleLabel->setStyleSheet("QLabel { color : lightgreen; font-size: 50pt; font-weight: bold; }");

    titleLabel->setAlignment(Qt::AlignCenter);

    startButton = new QPushButton("Новая игра");
    rulesButton = new QPushButton("Правила игры");
    exitButton = new QPushButton("Выход");

    startButton->setFixedWidth(300);

    startButton->setFixedHeight(48);
    rulesButton->setFixedHeight(48);
    exitButton->setFixedHeight(48);

    startButton->setStyleSheet("QPushButton {"
                          "    color: lightpink;"
                          "    background-color:  rgb(67, 57, 139);"
                          "}");
    rulesButton->setStyleSheet("QPushButton {"
                               "    color: lightpink;"
                               "    background-color:  rgb(67, 57, 139);"
                               "}");
    exitButton->setStyleSheet("QPushButton {"
                               "    color: lightpink;"
                               "    background-color:  rgb(67, 57, 139);"
                               "}");

    startButton->setFont(QFont("Arial", 18, QFont::Bold));
    rulesButton->setFont(QFont("Arial", 18, QFont::Bold));
    exitButton->setFont(QFont("Arial", 18, QFont::Bold));

    layout->addWidget(titleLabel);
    layout->addSpacing(30);
    layout->addWidget(startButton);
    layout->addWidget(rulesButton);
    layout->addWidget(exitButton);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(rulesButton, QPushButton::clicked, this, &MainWindow::showRules);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::exitGame);
}

void MainWindow::startGame()
{
    QMediaPlayer *player1 = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);
    player1->setAudioOutput(audioOutput);
    player1->setSource(QUrl("qrc:/sounds/button.wav"));
    audioOutput->setVolume(0.5);
    player1->play();

    Game *game = new Game();
    game->show();
    this->close();
}

void MainWindow::showRules()
{
    QMediaPlayer *player1 = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);
    player1->setAudioOutput(audioOutput);
    player1->setSource(QUrl("qrc:/sounds/button.wav"));
    audioOutput->setVolume(0.5);
    player1->play();

    QMessageBox::information(this, "Правила",
                             "⚓️ Правила игры:\n"
                             "- В игре 3 раунда.\n"
                             "- В первом раунде 1 вид монстров, который забирает 1 жизнь при столкновении.\n"
                             "- Во втором раунде 2 вида монстров, оба вида забирают по 1 жизни.\n"
                             "- В третьем раунде 3 вида монстров, новый забирает 2 жизни.\n"
                             "- Цель - пройти все уровни.\n\n"
                             "Удачи в игре!");
}
void MainWindow::exitGame()
{
    QMediaPlayer *player1 = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);
    player1->setAudioOutput(audioOutput);
    player1->setSource(QUrl("qrc:/sounds/button.wav"));
    audioOutput->setVolume(0.5);
    player1->play();

    QApplication::quit();
}
