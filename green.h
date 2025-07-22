#ifndef GREEN_H
#define GREEN_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Green : public QObject, public QGraphicsPixmapItem
{
public:
    Green();
    void fall();
};

#endif // GREEN_H

