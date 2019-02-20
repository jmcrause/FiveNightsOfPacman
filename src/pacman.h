#ifndef PACMAN_H
#define PACMAN_H

#include <QWidget>
#include <QLabel>
#include <QTimer>

class PacMan : public QLabel
{
    Q_OBJECT
public:
    explicit PacMan(QWidget *parent = 0);
    QTimer *tm1;
    void setDirection(bool, bool, bool, bool);
    void setSpeed(bool);


private:
    bool sprint, open, up, down, left, right, canMove;



signals:

public slots:


};

#endif // PACMAN_H
