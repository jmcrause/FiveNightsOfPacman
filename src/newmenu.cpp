#include "newmenu.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <stdlib.h>

NewMenu::NewMenu(QWidget *parent) :
    QWidget(parent)
{
    finish = false;
    start = false;
    isf = 0;

    this->showFullScreen();
    this->setStyleSheet("background->color: black");

    back = new QLabel(this);
    QPixmap pix1(":/pics/Capture.JPG");
    back->setPixmap(pix1);
    back->setFixedSize(1920, 1080);
    back->hide();


    //setup media object
       //
       menu1 = new Phonon::MediaObject();
       menu1->setCurrentSource(Phonon::MediaSource(QString("D:\\Werk\\3de jaar\\Semester 1\\EERI 316\\Menu\\vids\\Menu.mp4")));

       //setup player
       //
       vid1 = new Phonon::VideoPlayer(this);
       vid1->setFixedSize(QSize(1920,1080));
       vid1->move(0,0);
       vid1->show();
       connect(menu1, SIGNAL(finished()), menu1, SLOT(deleteLater()));
       vid1->play(menu1->currentSource());

       nGame = new QLabel(this);
       QPixmap pix(":/pics/pacman1.png");
       nGame->setPixmap(pix);
       nGame->setFixedSize(50, 50);
       nGame->move(425, 680);
       nGame->hide();

       conti = new QLabel(this);
       conti->setPixmap(pix);
       conti->setFixedSize(50, 50);
       conti->move(425, 805);
       conti->hide();

       tmp = new NewGame(this);

       tm1 = new QTimer(this);
       tm1->setInterval(50);
       connect(tm1, SIGNAL(timeout()), this, SLOT(timerTick()));
       tm1->start();

       tm2 = new QTimer(this);
       tm2->setInterval(46000);
       connect(tm2, SIGNAL(timeout()), this, SLOT(vidEnd()));
       tm2->start();

       tm3 = new QTimer(this);
       tm3->setInterval(5000);
       connect(tm3, SIGNAL(timeout()), this, SLOT(menuStart()));
       tm3->start();

       tm4 = new QTimer(this);
       tm4->setInterval(3000);
       connect(tm4, SIGNAL(timeout()), this, SLOT(nGameStart()));

}

void NewMenu::timerTick()
{
    if(QCursor::pos().x() >= 425 && QCursor::pos().x() <= 800 && start)
    {
        if(QCursor::pos().y() >= 680 && QCursor::pos().y() <= 730)
        {
            nGame->show();
            conti->hide();

            if(finish)
            {
                QPixmap pix1(":/pics/black.png");
                conti->setPixmap(pix1);
                conti->show();

                QPixmap pix(":/pics/pacman1.png");
                nGame->setPixmap(pix);
            }
        }

        if(QCursor::pos().y() >= 805 && QCursor::pos().y() <= 855)
        {
            nGame->hide();
            conti->show();

            if(finish)
            {
                QPixmap pix1(":/pics/black.png");
                nGame->setPixmap(pix1);
                nGame->show();

                QPixmap pix(":/pics/pacman1.png");
                conti->setPixmap(pix);
            }
        }
    }
}

void NewMenu::vidEnd()
{
    finish = true;
    back->show();
}

void NewMenu::menuStart()
{
    start = true;

}

void NewMenu::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
    {
        this->close();
    }
}

void NewMenu::mouseReleaseEvent(QMouseEvent *e)
{
    if(QCursor::pos().x() >= 425 && QCursor::pos().x() <= 800 && start)
    {
        if(QCursor::pos().y() >= 680 && QCursor::pos().y() <= 730)
        {
            tmp->move(610, 340);
            tmp->show();
            tmp->vid1->play(tmp->menu1->currentSource());
        }

        if(QCursor::pos().y() >= 805 && QCursor::pos().y() <= 855)
        {

        }
    }

    if(e->x() >= 700 && e->x() <= 1300)
    {
        if(e->y() >= 480 && e->y() <= 520)
        {
            m = new Map();
            m->hide();
            //m->show();
            conti->hide();
            nGame->hide();
            vid1->stop();
            tmp->hide();
            back->hide();
            tm4->start();

            QLabel *night1;
            night1 = new QLabel(this);
            night1->setText(" Night 1 \n 12:00 AM ");
            night1->setStyleSheet("background-color: black; color: rgb(255, 245, 255);  font: 40px courier;");
            night1->setFixedSize(250, 100);
            night1->move((this->width()-night1->width())/2, (this->height()-night1->height())/2);
            night1->show();
        }
    }
}

void NewMenu::nGameStart()
{
    m->show();

    if(isf != 0)
    {
        tm4->stop();
        this->close();
    }
    isf++;
}
