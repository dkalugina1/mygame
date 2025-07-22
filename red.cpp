#include "red.h"
#include <QPixmap>

Red::Red() {
    setPixmap(QPixmap(":/images/red.png").scaled(70, 70));
}

void Red::fall(){
    setY(y()+5);
}
