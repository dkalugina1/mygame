#include "player.h"
#include <QPixmap>

Player::Player() {
    setPixmap(QPixmap(":/images/hero.png").scaled(70, 70));
    movingLeft = false;
    movingRight = false;

}

void Player::move(){
    if(movingLeft && x()>0) setX(x()-10);
    if(movingRight && x()<430) setX(x()+10);
}

void Player::setMovingLeft(bool move) {
    movingLeft = move;
}
void Player::setMovingRight(bool move) {
    movingRight = move;
}
