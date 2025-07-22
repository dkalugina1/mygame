#include "game.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QApplication>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

Game::Game(QWidget *parent): QGraphicsView(parent), lives(3){

    scene = new QGraphicsScene(0, 0, 500, 700, this);
    setScene(scene);
    setFixedSize(500, 700);

    background = new QGraphicsPixmapItem(QPixmap(":/images/background.png").scaled(500,700));
    scene->addItem(background);

    //Создание главного героя
    player = new Player();
    player->setPos(215, 600);
    scene->addItem(player);

    livesText = new QGraphicsTextItem("Жизни: 3");
    livesText->setDefaultTextColor(Qt::white);
    livesText->setFont(QFont("Arial", 16));
    livesText->setPos(10,10);
    scene->addItem(livesText);

    timerText = new QGraphicsTextItem("Время: 10");
    timerText->setDefaultTextColor(Qt::white);
    timerText->setFont(QFont("Arial", 16));
    timerText->setPos(360, 10);
    scene->addItem(timerText);

    greenTimer = new QTimer(this);
    connect(greenTimer, &QTimer::timeout, this, &Game::spawnGreen);
    greenTimer->start(1000);

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &Game::updateGame);
    gameTimer->start(20);

    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &Game::decreaseTime);
    countdownTimer->start(1000);

    continueButton = new QPushButton("Продолжить игру", this);
    continueButton->setGeometry(150, 350, 200, 50);
    continueButton->hide();
    connect(continueButton, &QPushButton::clicked, this, &Game::nextLevel);

    exitButton = new QPushButton("Выйти из игры", this);
    exitButton->setGeometry(150, 350, 200, 50);
    exitButton->hide();
    connect(exitButton, &QPushButton::clicked, this, &Game::exitGame);

    player2->setAudioOutput(audioOutput);
    player2->setSource(QUrl("qrc:/sounds/game2.wav"));
    player2->play();
}

void Game::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_Left) player->setMovingLeft(true);
    if(event->key() == Qt::Key_Right) player->setMovingRight(true);
}

void Game::keyReleaseEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Left) player->setMovingLeft(false);
    if(event->key() == Qt::Key_Right) player->setMovingRight(false);
}

void Game::spawnGreen(){
    Green *green = new Green();
    green->setPos(rand() % 450, -50);
    scene->addItem(green);
    greens.append(green);
}

void Game::spawnRED(){
    Red *red = new Red();
    red->setPos(rand() % 450, -50);
    scene->addItem(red);
    reds.append(red);
}

void Game::spawnBlack(){
    Black *black = new Black();
    black->setPos(rand() % 450, -50);
    scene->addItem(black);
    blacks.append(black);
}

void Game::updateGame(){
    player->move();

    QMediaPlayer *player1 = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);
    player1->setAudioOutput(audioOutput);

   /*
     if(timeRemaining <= 0){

        if(level == 1){
            //Завершение 1 уровня
            greenTimer->stop();
            gameTimer->stop();
            continueButton->show();
        }else if (level == 2) {
            //Завершение 2 уровня
            greenTimer->stop();
            gameTimer->stop();
            redTimer->stop();
            continueButton->show();
        }else if(level == 3){
            endGame();
        }
        return;
    }*/

    for(auto it = greens.begin(); it != greens.end(); ){
        Green *green = *it;
        green->fall();

        if(green->collidesWithItem(player)){
            scene->removeItem(green);
            delete green;
            it = greens.erase(it);
            lives--;
            player1->setSource(QUrl("qrc:/sounds/hit.wav"));
            audioOutput->setVolume(0.5);
            player1->play();

            //Обновление текста
            livesText->setPlainText(QString("Жизни: %1").arg(lives));
            if(lives <= 0){
                player2->stop();
                livesText->setPlainText("Игра окончена!");
                greenTimer->stop();
                gameTimer->stop();
                countdownTimer->stop();

                QMessageBox::information(this, "Поражение!", "Пришельцы выиграли!");

                MainWindow *newGame = new MainWindow();
                newGame->show();
                this->close();
            }
        } else if (green->y() > 700) {
            scene->removeItem(green);
            delete green;
            it = greens.erase(it);
        } else{
            ++it;
        }
    }

    if(level >= 2){
        for(auto it = reds.begin(); it != reds.end(); ){
            Red *red = *it;
            red->fall();

            if(red->collidesWithItem(player)){
                scene->removeItem(red);
                delete red;
                it = reds.erase(it);
                lives--;
                player1->setSource(QUrl("qrc:/sounds/hit1.wav"));
                audioOutput->setVolume(0.5);
                player1->play();

                //Обновление текста
                livesText->setPlainText(QString("Жизни: %1").arg(lives));
                if(lives <= 0){
                    player2->stop();
                    livesText->setPlainText("Игра окончена!");
                    redTimer->stop();
                    gameTimer->stop();
                    countdownTimer->stop();

                    QMessageBox::information(this, "Поражение!", "Пришельцы выиграли!");

                    MainWindow *newGame = new MainWindow();
                    newGame->show();
                    this->close();
                }
            } else if (red->y() > 700) {
                scene->removeItem(red);
                delete red;
                it = reds.erase(it);
            } else{
                ++it;
            }
        }
        if (level == 3){
            for(auto it = blacks.begin(); it != blacks.end(); ){
                Black *black = *it;
                black->fall();

                if(black->collidesWithItem(player)){
                    player1->setSource(QUrl("qrc:/sounds/hit2.wav"));
                    audioOutput->setVolume(0.5);
                    player1->play();
                    scene->removeItem(black);
                    delete black;
                    it = blacks.erase(it);
                    lives-=lives;
                    livesText->setPlainText(QString("Жизни: %1").arg(lives));
                    if(lives <= 0){
                        player2->stop();
                        redTimer->stop();
                        blackTimer->stop();
                        gameTimer->stop();
                        countdownTimer->stop();

                        QMessageBox::information(this, "Поражение!", "Пришельцы выиграли!");
                        livesText->setPlainText("Игра окончена!");

                        MainWindow *newGame = new MainWindow();
                        newGame->show();
                        this->close();
                    }
                    }

                    else if (black->y() > 700) {
                        scene->removeItem(black);
                        delete black;
                        it = blacks.erase(it);
                    } else{
                        ++it;
                    }

            }
    }
 }
}

void Game::nextLevel(){
    QMediaPlayer *player1 = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);
    player1->setAudioOutput(audioOutput);

    if (level == 1){
        player2->play();
        player1->setSource(QUrl("qrc:/sounds/newlevel.wav"));
        audioOutput->setVolume(0.5);
        player1->play();

        level = 2;
        timeRemaining = 20;
        timerText->setPlainText(QString("Время: %1").arg(timeRemaining));
        continueButton->hide();

        countdownTimer->start(1000);
        greenTimer->start(800);
        redTimer = new QTimer(this);
        connect(redTimer, &QTimer::timeout, this, &Game::spawnRED);
        redTimer->start(2000);

        gameTimer->start(20);
    }
    else if (level == 2){
        player2->play();
        player1->setSource(QUrl("qrc:/sounds/newlevel.wav"));
        audioOutput->setVolume(0.5);
        player1->play();

        level = 3;
        timeRemaining = 30;
        timerText->setPlainText(QString("Время: %1").arg(timeRemaining));
        continueButton->hide();

        countdownTimer->start(1000);
        greenTimer->start(800);
        redTimer = new QTimer(this);
        blackTimer = new QTimer(this);
        connect(redTimer, &QTimer::timeout, this, &Game::spawnRED);
        redTimer->start(2000);
        connect(blackTimer, &QTimer::timeout, this, &Game::spawnBlack);
        blackTimer->start(3000);

        gameTimer->start(20);
    }
}

void Game::decreaseTime(){
    timeRemaining--;
    timerText->setPlainText(QString("Время: %1").arg(timeRemaining));

    if(timeRemaining <= 0){
        countdownTimer->stop();
        if(level == 1){
            //Завершение 1 уровня
            player2->stop();
            greenTimer->stop();
            gameTimer->stop();
            continueButton->show();

        }else if (level == 2) {
            //Завершение 2 уровня
            player2->stop();
            greenTimer->stop();
            gameTimer->stop();
            continueButton->show();
        } else if(level == 3){
            endGame();
        }
    }
}

void Game::endGame(){
    greenTimer->stop();
    gameTimer->stop();
    if(redTimer) redTimer->stop();
    if(blackTimer) blackTimer->stop();
    livesText->setPlainText("Игра окончена!");
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Победа!", "Вы выиграли! Сыграть ещё раз?", QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes){
            Game *newGame = new Game();
            newGame->show();
            this->close();
        } else {
            MainWindow *newGame = new MainWindow();
            newGame->show();
            this->close();
        }

        return;
}

void Game::exitGame(){
    QApplication::quit();
}
