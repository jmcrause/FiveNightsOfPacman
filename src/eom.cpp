#include "eom.h"
#include <QPixmap>
#include <QFile>
#include <QIODevice>
#include <QDebug>

eom::eom(QWidget *parent) :
    QWidget(parent)
{

this->showFullScreen();
this->hide();
this->setStyleSheet("background-color: rgb(5,64,96);");

banner = new QLabel(this);
QPixmap p (":/Picture/employeeotm.jpg");
banner->setPixmap(p);
banner->setFixedSize(p.width(), p.height());
banner->show();

menu = new QPushButton(this);
menu->move(20,730);
menu->setText("Main Menu");
menu->setStyleSheet("Background-color: white");
menu->show();

fn = "entry.dat";
QFile f(fn);

f.open(QIODevice::Text | QIODevice::ReadOnly);

if(f.isOpen())
{
    while (!f.atEnd())
    {
       QByteArray l = f.readLine().trimmed();
       QList<QByteArray> array = l.split('\t');

       if(array.size() > 1)
       {
           int telling = array[0].toInt();
           entry.insert(telling,array[1]);
       }

    }
    f.close();
}

}

void eom::setEntry(int score, QByteArray name)
{
      entry.insert(score, name);

      QFile f(fn);
      f.open(QIODevice::Text | QIODevice::Truncate | QIODevice::WriteOnly);

      if (f.isOpen())
      {
          int teller = 0;
          QMapIterator <int, QByteArray> iterate(entry);
          iterate.toBack();

      while( teller < 10 && iterate.hasPrevious())
      {
          iterate.previous();
          int num = iterate.key();
          QByteArray name = iterate.value();
          QByteArray info = QByteArray::number(num);

          info.append("\t");
          info.append(name);
          info.append("\n");
          f.write(info);
          ++teller;

      }
      f.close();
    }
 }

void eom::printEmployee()
{
   QMapIterator <int, QByteArray> iterate2(entry);
   iterate2.toFront();

   int teller2 = 0;

   while(iterate2.hasNext() && teller2 < 10)
   {
   iterate2.next();
   QByteArray employee = iterate2.value();

     names = new QLabel(this);
     names->clear();
     names->setText(employee);
     names->setStyleSheet("font: 40px courier; color:rgb(255,245,255)");
     names->move(200, 250 + teller2*40);
     names->show();

   ++teller2;
  }
}

void eom::clear()
{
  entry.clear();
  QFile f(fn);
  f.open(QIODevice::Truncate | QIODevice::WriteOnly);
  f.close();
}





