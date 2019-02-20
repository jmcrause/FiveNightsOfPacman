#ifndef STORY_H
#define STORY_H

#include <QWidget>
#include <QLabel>
#include <QTextBrowser>
#include <QPushButton>

class story : public QWidget
{
    Q_OBJECT
public:
    explicit story(QWidget *parent = 0);
     QLabel *header;
     QTextBrowser *browse;
     QLabel *freddy;
     QPushButton *mmenu;


signals:

public slots:

};

#endif // STORY_H
