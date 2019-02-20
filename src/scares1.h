#ifndef SCARES1_H
#define SCARES1_H

#include <QWidget>
#include <Phonon/MediaObject>
#include <Phonon/VideoPlayer>
#include <QTimer>

class scares1 : public QWidget
{
    Q_OBJECT
public:
    explicit scares1(QWidget *parent = 0);
    void Bonnie();

private:
    Phonon::VideoPlayer *vid2;
    Phonon::MediaObject *bonny;

    QTimer *tm;


signals:

public slots:
    void showMenu();

};

#endif // SCARES1_H
