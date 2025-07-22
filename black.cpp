#include "black.h"

Black::Black() {
    setPixmap(QPixmap(":/images/black.png").scaled(70, 70));
}

void Black::fall(){
    setY(y()+5);
}
