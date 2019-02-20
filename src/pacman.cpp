#include "pacman.h"

PacMan::PacMan(QWidget *parent) :
    QLabel(parent)
{
    int x = 19*50;
    int y = 35*50;
    up = down = left = right = false;
    open= canMove = true;


    QPixmap pix(":/pacman/pacman1.png");
    setPixmap(pix);
    setFixedSize(pix.width(), pix.height());
    move(x, y);
    show();
}

void PacMan::setDirection(bool l, bool r, bool u, bool d)
{
    left = l;
    right = r;
    up = u;
    down = d;

    tm1->start();
}
