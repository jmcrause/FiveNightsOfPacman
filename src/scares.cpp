#include "scares.h"
#include <QProcess>

Scares::Scares(QWidget *parent) :
    QWidget(parent)
{    
    this->showFullScreen();
    this->setStyleSheet("background-color: black;");

    tm =new QTimer();
    tm->setInterval(1000);
    connect(tm, SIGNAL(timeout()), this, SLOT(close()));

    freddy = new Phonon::MediaObject();
    freddy->setCurrentSource(Phonon::MediaSource(QString("D:/Werk/3de jaar/Semester 1/EERI 316/Menu/vids/Freddy.mp4")));

    //setup player
    //
    vid1 = new Phonon::VideoPlayer(this);
    vid1->setFixedSize(QSize(1920,1080));
    vid1->move(0,0);
    vid1->show();

    connect(freddy, SIGNAL(finished()), freddy, SLOT(deleteLater()));
    vid1->play(freddy->currentSource());
    vid1->pause();

    hide();
}

void Scares::Freddy()
{
    //connect(freddy, SIGNAL(finished()), freddy, SLOT(deleteLater()));
    vid1->play(freddy->currentSource());
    connect(vid1, SIGNAL(finished()), this, SLOT(showMenu()));
}

void Scares::showMenu()
{
    QString name = "D:\\Werk\\3de jaar\\Semester 1\\EERI 316\\Menu-build-desktop\\debug\\Menu.exe";
    QProcess::startDetached(name, QStringList() << "");
    tm->start();
}

