#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include "player.h"
#include "green.h"
#include "red.h"
#include "black.h"
#include <QApplication>
#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QLabel>


class Game : public QGraphicsView{
    Q_OBJECT

public:
    Game(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    QMediaPlayer *player2 = new QMediaPlayer(this);
    QAudioOutput *audioOutput = new QAudioOutput(this);

private:
    QGraphicsScene *scene;
    Player *player;
    QTimer *greenTimer;
    QTimer *gameTimer;
    QTimer *redTimer;
    QTimer *blackTimer;
    QTimer *countdownTimer;
    QList<Green*> greens;
    QList<Red*> reds;
    QList<Black*> blacks;
    int lives;
    int level = 1;
    QGraphicsTextItem *livesText;
    QGraphicsTextItem *timerText;
    QGraphicsPixmapItem *background;
    int timeRemaining = 10;
    QPushButton *continueButton;
    QPushButton *replayButton;
    QPushButton *exitButton;
    void spawnGreen();
    void spawnRED();
    void spawnBlack();
    void updateGame();
    void nextLevel();
    void endGame();
    void decreaseTime();
    void exitGame();

};

#endif // GAME_H
