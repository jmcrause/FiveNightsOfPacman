#ifndef FORMFILL_H
#define FORMFILL_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <qmainwindow.h>
#include <eom.h>

class FormFill : public QWidget
{
    Q_OBJECT
public:
    explicit FormFill(QWidget *parent = 0);
    QLabel *congrats;
    QLabel *message1;
    QLabel *message2;
    QLineEdit *box;
    QPushButton *pb;

    QString name;
    eom *e;


signals:

public slots:
 void saveFunction();

};

#endif // FORMFILL_H
