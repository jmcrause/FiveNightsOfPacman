#ifndef SCARES_H
#define SCARES_H

#include <QWidget>
#include <Phonon/MediaObject>
#include <Phonon/VideoPlayer>
#include <QTimer>

class Scares : public QWidget
{
    Q_OBJECT
public:
    explicit Scares(QWidget *parent = 0);
    void Freddy();

private:
    Phonon::VideoPlayer *vid1;
    Phonon::MediaObject *freddy;

    QTimer *tm;


signals:

public slots:
    void showMenu();

};

#endif // SCARES_H
