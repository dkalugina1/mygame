#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Player();
    void move();
    void setMovingLeft(bool move);
    void setMovingRight(bool move);
private:
    bool movingLeft;
    bool movingRight;
};

#endif // PLAYER_H
