#ifndef SCARES2_H
#define SCARES2_H

#include <QWidget>
#include <Phonon/MediaObject>
#include <Phonon/VideoPlayer>
#include <QTimer>

class scares2 : public QWidget
{
    Q_OBJECT
public:
    explicit scares2(QWidget *parent = 0);
    void Chika();

private:
    Phonon::VideoPlayer *vid3;
    Phonon::MediaObject *chika;

    QTimer *tm;


signals:

public slots:
    void showMenu();

};

#endif // SCARES2_H
