#ifndef ANIMATRONICS_H
#define ANIMATRONICS_H

#include <QWidget>
#include <QLabel>

class Animatronics : public QLabel
{
    Q_OBJECT
public:
    explicit Animatronics(QWidget *parent = 0);
    void Freddy();
    void Bonnie();
    void Chika();
    void Foxy();

private:
    int animal;

signals:

public slots:

};

#endif // ANIMATRONICS_H
