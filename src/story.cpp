#include "story.h"

story::story(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowState(Qt::WindowFullScreen);
    this->setStyleSheet("Background-color: black");

    freddy = new QLabel(this);
    QPixmap p (":/Picture/gfreddy.png");
    freddy->setPixmap(p);
    freddy->setFixedSize(p.width(), p.height());
    freddy->move(800, 100);
    freddy->show();

    header = new QLabel(this);
    header->setText("The Story");
    header->setStyleSheet("font: 40px courier; color:rgb(255,245,255)");
    header->move(300,10);

    mmenu = new QPushButton(this);
    mmenu->move(20,730);
    mmenu->setText("Main Menu");
    mmenu->setStyleSheet("Background-color: white");
    mmenu->show();

    browse = new QTextBrowser(this);
    browse->setFixedSize(700, 500);
    browse->setStyleSheet("Background-color: white");
    browse->setStyleSheet("font: 16px courier; color:rgb(255,245,255)");
    browse->move(50, 60);
    browse->setText("The business initially began as Fazbear's diner. This was a small venue for children parties, with only a Golden Freddy working there. Since Golden Freddy is a hybrid and can be operated by endo-skeleton or human, it was operated by a human at the time. During that time, a person called 'the purple guy' lured one of the children outside and killed the child. The child's death caused negative public relations and the diner closed down.\n\n"
                    "Some time later, the business reopened as Freddy Fazbear's Pizzeria. Golden Freddy together with Golden Bonnie were entertainers. But the purple disguised himself as an employee and wore the Golden Bonnie suit to lure 5 more children to the storage room to murder them.\n\n"
                    "The business moved to a third location and got new animatronics. The spirit of the first murdered child took the place of one of the new characters called 'The Puppet' and put the rest of  murdered children's bodies into the animatronics suits: Freddy, Chica, Foxy, Bonnie and Golden Freddy. \n\n"
                    "Due to an 'unfortunate bite incident', the business moved once again. The animatronics, on the hunt for the purple guy, roams the halls to find revenge. With purple guy (or pac-guard) uncaught and reinstated, he must survive the night shift.\n\n"
                    "Welcome to Five Nights at Pacman");

}
