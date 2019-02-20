#ifndef NEWMENU_H
#define NEWMENU_H

#include <QWidget>
#include <QMainWindow>
#include <Phonon/VideoPlayer>
#include <Phonon/MediaObject>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QTimer>
#include "map.h"
#include "newgame.h"

class NewMenu : public QWidget
{
    Q_OBJECT
public:
    explicit NewMenu(QWidget *parent = 0);

private:
    Phonon::VideoPlayer *vid1;
    Phonon::MediaObject *menuMain, *menu1;
    QLabel *nGame, *conti, *back;
    QTimer *tm1, *tm2, *tm3, *tm4, *t;
    bool finish, start;
    int isf;
    NewGame *tmp;
    Map *m;

protected:
    void keyPressEvent(QKeyEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private slots:
    void timerTick();
    void vidEnd();
    void menuStart();
    void nGameStart();
};

#endif // NEWMENU_H
