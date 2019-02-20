#include "scares1.h"
#include <QProcess>

scares1::scares1(QWidget *parent) :
    QWidget(parent)
{
    this->showFullScreen();
    this->setStyleSheet("background-color: black;");

    tm =new QTimer();
    tm->setInterval(1000);
    connect(tm, SIGNAL(timeout()), this, SLOT(close()));

    bonny = new Phonon::MediaObject();
    bonny->setCurrentSource(Phonon::MediaSource(QString("D:/Werk/3de jaar/Semester 1/EERI 316/Menu/vids/Bonnie.mp4")));

    //setup player
    //

    vid2 = new Phonon::VideoPlayer(this);
    vid2->setFixedSize(QSize(1920,1080));
    vid2->move(0,0);
    vid2->show();

    connect(bonny, SIGNAL(finished()), bonny, SLOT(deleteLater()));
    vid2->play(bonny->currentSource());
    vid2->pause();

    hide();
}

void scares1::Bonnie()
{
    //connect(bonny, SIGNAL(finished()), bonny, SLOT(deleteLater()));
    vid2->play(bonny->currentSource());
    connect(vid2, SIGNAL(finished()), this, SLOT(showMenu()));
}

void scares1::showMenu()
{
    QString name = "D:\\Werk\\3de jaar\\Semester 1\\EERI 316\\Menu-build-desktop\\debug\\Menu.exe";
    QProcess::startDetached(name, QStringList() << "");
    tm->start();
}

