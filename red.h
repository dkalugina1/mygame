#ifndef RED_H
#define RED_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Red : public QObject, public QGraphicsPixmapItem
{
public:
    Red();
    void fall();
};

#endif // RED_H

