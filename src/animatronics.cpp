#include "animatronics.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>


Animatronics::Animatronics(QWidget *parent) :
    QLabel(parent)
{
    animal = 0;
    setFixedSize(50, 50);
}

void Animatronics::Freddy()
{
    QPixmap pix(":/animatronics/Freddie.png");
    setPixmap(pix);
    animal = 0;
}

void Animatronics::Bonnie()
{
    QPixmap pix(":/animatronics/Bonnie.png");
    setPixmap(pix);
    animal = 1;
}

void Animatronics::Chika()
{
    QPixmap pix(":/animatronics/Chika.png");
    setPixmap(pix);
    animal = 2;
}

void Animatronics::Foxy()
{
    QPixmap pix(":/animatronics/Foxy.png");
    setPixmap(pix);
    animal = 3;
}
