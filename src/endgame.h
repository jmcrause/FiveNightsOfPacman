#ifndef ENDGAME_H
#define ENDGAME_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <Phonon/MediaObject>
#include <Phonon/VideoPlayer>
#include <formfill.h>

class EndGame :  public QWidget
{
    Q_OBJECT
public:
    explicit EndGame(QWidget *parent = 0);
    void nextDay();
    void playVid();

private:
    int i;
    QLabel *night2;
    QTimer *tm, *wait;


    Phonon::VideoPlayer *vid1;
    Phonon::MediaObject *won;

    FormFill *f;

signals:

public slots:
    void nextPage();
    void waitForNext();
};

#endif // ENDGAME_H
