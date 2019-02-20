#ifndef STARTNIGHT2_H
#define STARTNIGHT2_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include "nighttwo.h"
#include <Phonon/MediaObject>

class StartNight2 : public QWidget
{
    Q_OBJECT
public:
    explicit StartNight2(QWidget *parent = 0);
    void nextDay();
    void playVid();

private:
    int i;
    QLabel *night2;
    QTimer *tm, *wait;
    NightTwo *m;

    Phonon::VideoPlayer *vid1;
    Phonon::MediaObject *won;

signals:

public slots:
    void nextPage();
    void waitForNext();


};

#endif // STARTNIGHT2_H
