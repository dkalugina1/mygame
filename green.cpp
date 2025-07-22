#include "green.h"
#include <QPixmap>

Green::Green() {
    setPixmap(QPixmap(":/images/green.png").scaled(70, 70));
}

void Green::fall(){
    setY(y()+5);
}
