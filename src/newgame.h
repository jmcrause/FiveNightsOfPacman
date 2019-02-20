#ifndef NEWGAME_H
#define NEWGAME_H

#include <QLabel>
#include <QWidget>
#include <Phonon/VideoPlayer>
#include <Phonon/MediaObject>
#include <QTimer>
#include <QMouseEvent>
#include "map.h"

class NewGame : public QLabel
{
    Q_OBJECT

public:
    explicit NewGame(QWidget *parent = 0);

    Phonon::VideoPlayer *vid1;
    Phonon::MediaObject *menuMain, *menu1;

private:
    QLabel *ngMenu;
    QTimer *tm1;
    Map *m;

private slots:
    void timer();

protected:
    void mousePressEvent(QMouseEvent *ev);
};

#endif // NEWGAME_H
