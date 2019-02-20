#include "formfill.h"
#include "mainwindow.h"

FormFill::FormFill(QWidget *parent) :
    QWidget(parent)
{

    e = new eom;
    //e->clear();
    this->setFixedSize(650,250);
    this->setStyleSheet("Background-color: black");

    congrats = new QLabel(this);
    congrats->setText("Congratulations!");
    congrats->setStyleSheet("font: 30px courier; color:rgb(255,245,255)");
    congrats->move(200,10);

    message1 = new QLabel(this);
    message1->setText("You are the new employee of the month");
    message1->setStyleSheet("font: 20px courier; color:rgb(255,245,255)");
    message1->move(113,50);

    message2 = new QLabel(this);
    message2->setText("Please fill in your details below:");
    message2->setStyleSheet("font: 15px courier; color:rgb(255,245,255)");
    message2->move(20,130);

    box = new QLineEdit(this);
    box->move(20,150);
    box->setFixedSize(400, 20);
    box->setStyleSheet("Background-color: white");
    box->show();

    pb = new QPushButton(this);
    pb->move(20,180);
    pb->setText("Save");
    pb->setStyleSheet("Background-color: white");
    pb->show();
    connect(pb,SIGNAL(clicked()),this,SLOT(saveFunction()));
}

void FormFill::saveFunction()
{
   name = "";
   name = box->text();
   QByteArray b = name.toLatin1();
   const char *ch = b.data();
   e->setEntry(100, ch);
   e->printEmployee();
   box->clear();
   e->show();

   this->close();
}


