#ifndef BLACK_H
#define BLACK_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Black : public QObject, public QGraphicsPixmapItem
{
public:
    Black();
    void fall();
};

#endif // BLACK_H
