#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Phonon/VideoPlayer>
#include <Phonon/MediaObject>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QTimer>
#include "map.h"
#include "newgame.h"
#include "nighttwo.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Phonon::VideoPlayer *vid1;
    Phonon::MediaObject *menuMain, *menu1;
    QLabel *nGame, *conti, *back;
    QTimer *tm1, *tm2, *tm3, *tm4, *t;
    bool finish, start;
    int isf;
    NewGame *tmp;
    Map *m;
    //NightTwo *m;

protected:
    void keyPressEvent(QKeyEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private slots:
    void timerTick();
    void vidEnd();
    void menuStart();
    void nGameStart();
};

#endif // MAINWINDOW_H
