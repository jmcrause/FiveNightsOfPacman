#ifndef EOM_H
#define EOM_H

#include <QWidget>
#include <QLabel>
#include <QMultiMap>
#include <QByteArray>
#include <QString>
#include <QPushButton>

class eom : public QWidget
{
    Q_OBJECT
public:
    explicit eom(QWidget *parent = 0);

    QLabel *banner;
    QLabel *names;

    QMultiMap <int, QByteArray> entry;
    QString fn;
    QPushButton *menu;

    void setEntry();
    void setEntry(int , QByteArray );
    void printEmployee();
    void clear();


signals:

public slots:

};

#endif // EOM_H
