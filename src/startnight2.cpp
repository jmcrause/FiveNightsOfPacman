#include "startnight2.h"

StartNight2::StartNight2(QWidget *parent) :
    QWidget(parent)
{
    this->showFullScreen();
    this->hide();
    won = new Phonon::MediaObject(this);
    won->setCurrentSource(Phonon::MediaSource(QString("D:\\Werk\\3de jaar\\Semester 1\\EERI 316\\Menu\\vids\\6AM.mp4")));

    //setup player
    //
    vid1 = new Phonon::VideoPlayer(this);
    vid1->setFixedSize(QSize(1920,1080));
    vid1->move(0,0);
    connect(won, SIGNAL(finished()), won, SLOT(deleteLater()));
    vid1->showFullScreen();

    vid1->play(won->currentSource());
    vid1->pause();

    i = 0;

}

void StartNight2::nextPage()
{
    if(i == 0)
    {
        m->show();
        i++;
    }
    else
    {
        tm->stop();
        this->close();
    }
}

void StartNight2::waitForNext()
{
    wait->stop();
    nextDay();
}

void StartNight2::nextDay()
{
    tm = new QTimer(this);
    tm->setInterval(4000);
    connect(tm, SIGNAL(timeout()), this, SLOT(nextPage()));
    tm->start();

    QLabel *night2;
    night2 = new QLabel(this);
    night2->setText(" Night 2 \n 12:00 AM ");
    night2->setStyleSheet("background-color: black; color: rgb(255, 245, 255);  font: 40px courier;");
    night2->setFixedSize(250, 100);
    night2->move((this->width()-night2->width())/2, (this->height()-night2->height())/2);
    night2->show();

    //m = new Map();
    m = new NightTwo();
    m->hide();
}

void StartNight2::playVid()
{
    vid1->play(won->currentSource());

    wait = new QTimer(this);
    wait->setInterval(10000);
    connect(wait, SIGNAL(timeout()), this, SLOT(waitForNext()));
    wait->start();
}
