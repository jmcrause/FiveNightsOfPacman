#include "newgame.h"

NewGame::NewGame(QWidget *parent) :  QLabel(parent)
{
    menu1 = new Phonon::MediaObject();
    menu1->setCurrentSource(Phonon::MediaSource(QString("D:\\Werk\\3de jaar\\Semester 1\\EERI 316\\Menu\\click.wav")));

    //setup player
    //
    vid1 = new Phonon::VideoPlayer(this);
    //vid1->setFixedSize(QSize(1920,1080));
    //vid1->move(0,0);
    //vid1->show();
    //connect(menu1, SIGNAL(finished()), menu1, SLOT(deleteLater()));
    //vid1->play(menu1->currentSource());

    setStyleSheet("background-color: black; color: rgb(255, 245, 255);  font: 40px courier; border: 2px solid white;");
    setText(" >> New Single Player Game \n \n    New Multiplayer Game");
    setFixedSize(700, 400);

    tm1 = new QTimer(this);
    tm1->setInterval(50);
    connect(tm1, SIGNAL(timeout()), this, SLOT(timer()));
    tm1->start();
}

void NewGame::timer()
{
    if(QCursor::pos().x() >= 700 && QCursor::pos().x() <= 1300)
    {
        if(QCursor::pos().y() >= 480 && QCursor::pos().y() <= 520)
        {
            setText(" >> New Single Player Game \n \n    New Multiplayer Game");
        }

        if(QCursor::pos().y() >= 560 && QCursor::pos().y() <= 600)
        {
            setText("    New Single Player Game \n \n >> New Multiplayer Game");
        }
    }
}

void NewGame::mousePressEvent(QMouseEvent *ev)
{

}
