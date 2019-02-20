#ifndef NIGHTTWO_H
#define NIGHTTWO_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>
#include "pacman.h"
#include <QTimer>
#include "animatronics.h"
#include <Phonon/MediaObject>
#include <Phonon/VideoPlayer>
#include "scares.h"
#include "scares1.h"
#include "scares2.h"
#include "endgame.h"

class NightTwo : public QWidget
{
    Q_OBJECT
public:
    explicit NightTwo(QWidget *parent = 0);
    void grid();
    void setSpeed(bool);
    void addScares();
    void flashLight();
    void flashInitialize();

private:
    QLabel *block, *block3, *curtain, *checkPoints[11], *tables[10], *light[8], *redBlock;
    bool canMove[50][50], isWall[50][50], sprint, flash, checked[11];
    PacMan *pac;
    QTimer *tm, *tB, *tC, *tF, *tP, *t, *cB, *cC, *cF, *foxMove;
    bool open, up, down, left, right, chaseB, chaseC, chaseF, soundB, soundC, soundF;
    int speed, flapspeed, f;
    int mouth;
    int scrollX, scrollY;
    int pythB, pythC, pythF;
    int lenxB;
    int lenyB;
    int lenxC;
    int lenyC;
    int lenxF;
    int lenyF;
    int lenxFox;
    int lenyFox;
    Animatronics *bon, *chik, *fred, *fox;
    Scares *scare;
    scares1 *scare1;
    scares2 *scare2;

    Phonon::VideoPlayer *vid1;
    Phonon::MediaObject *freddy, *bonny, *chika, *foxSong;
    Phonon::MediaObject *music, *fright, *intro;

    EndGame *go;

protected:
    void keyPressEvent(QKeyEvent *e);

public slots:
    void MoveDirect();
    void trackB();
    void trackC();
    void trackF();
    void trackPac();
    void phase1();

    void BonnieRun();
    void ChikaRun();
    void FreddyRun();
    void FoxyMove();

};

#endif // NIGHTTWO_H
