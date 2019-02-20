#include "scares2.h"
#include <QProcess>
#include <QApplication>

scares2::scares2(QWidget *parent) :
    QWidget(parent)
{
    this->showFullScreen();
    this->setStyleSheet("background-color: black;");

    tm =new QTimer();
    tm->setInterval(1000);
    connect(tm, SIGNAL(timeout()), this, SLOT(close()));

    chika = new Phonon::MediaObject();
    chika->setCurrentSource(Phonon::MediaSource(QString("D:/Werk/3de jaar/Semester 1/EERI 316/Menu/vids/Chika.mp4")));

    //setup player
    //
    vid3 = new Phonon::VideoPlayer(this);
    vid3->setFixedSize(QSize(1920,1080));
    vid3->move(0,0);
    vid3->show();

    connect(chika, SIGNAL(finished()), chika, SLOT(deleteLater()));
    vid3->play(chika->currentSource());
    vid3->pause();

    hide();
}

void scares2::Chika()
{
    //connect(chika, SIGNAL(finished()), chika, SLOT(deleteLater()));
    vid3->play(chika->currentSource());
    connect(vid3, SIGNAL(finished()), this, SLOT(showMenu()));
}

void scares2::showMenu()
{
    QString name = "D:\\Werk\\3de jaar\\Semester 1\\EERI 316\\Menu-build-desktop\\debug\\Menu.exe";
    QProcess::startDetached(name, QStringList() << "");
    tm->start();
}

