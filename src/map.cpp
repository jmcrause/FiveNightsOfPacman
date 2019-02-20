#include "map.h"
#include <math.h>
#include <qmath.h>
#include <stdlib.h>
#include <time.h>
#include <QDebug>
#include <QPixmap>
#include <QTransform>

Map::Map(QWidget *parent) :
    QWidget(parent)
{
    flash = chaseB = chaseC = chaseF = false;
    soundB = soundC = soundF = true;
    checks = 0;

    for(int k = 0; k <= 10; k++)
    {
        checked[k] = false;
    }

    t = new QTimer;
    t->setInterval(95185);

    connect(t,SIGNAL(timeout()),this,SLOT(phase1()));
    music = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource("D:/Werk/3de jaar/Semester 1/EERI 316/Menu/Audio/Gameplay.wav"));
    t->start();
    music->play();

    fright = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource("D:/Werk/3de jaar/Semester 1/EERI 316/Menu/Audio/sight.wma"));
    //fright->play();
    //fright->pause();

    scare = new Scares();
    scare1 = new scares1();
    scare2 = new scares2();

    sprint = false;
    speed = 2;
    flapspeed = 10;
    mouth = 0;
    srand(time(NULL));

    this->showFullScreen();
    this->setStyleSheet("background-color: black");

    grid();

    int randx = rand()%40;
    int randy = rand()%40;

    while(canMove[randx][randy] == false || (randy >=  29 && randx >=14 && randx <= 25) )
    {
        randx = rand()%40;
        randy = rand()%40;
    }

    bon = new Animatronics(this);
    bon->setStyleSheet("background-color: transparent;");
    bon->Bonnie();
    bon->move(randx*50,randy*50);
    bon->hide();

    randx = rand()%40;
    randy = rand()%40;

    while(canMove[randx][randy] == false || (randy >=  29 && randx >=14 && randx <= 25) )
    {
        randx = rand()%40;
        randy = rand()%40;
    }

    chik = new Animatronics(this);
    chik->setStyleSheet("background-color: transparent;");
    chik->Chika();
    chik->move(randx*50,randy*50);
    chik->hide();

    randx = rand()%40;
    randy = rand()%40;

    while(canMove[randx][randy] == false || (randy >=  29 && randx >=14 && randx <= 25) )
    {
        randx = rand()%40;
        randy = rand()%40;
    }

    fred = new Animatronics(this);
    fred->setStyleSheet("background-color: transparent;");
    fred->Freddy();
    fred->move(randx*50,randy*50);
    fred->hide();

    pac = new PacMan(this);
    pac->setStyleSheet("background-color: transparent;");

    tm = new QTimer(this);
    tm->setInterval(20);
    connect(tm, SIGNAL(timeout()), this, SLOT(MoveDirect()));


    scrollX = (this->width()-2000)/2;
    scrollY = this->height()-2000;
    this->scroll(scrollX, scrollY);
    this->setCursor(Qt::BlankCursor);
    //this->scroll(this->width()-2020, this->height()-2020);

    lenxC = chik->x() - pac->x();
    lenyC = chik->y() - pac->y();
    pythC = sqrt(pow(lenxC, 2)+ pow(lenyC, 2));

    tC = new QTimer;
    tC->setInterval(10);
    connect(tC, SIGNAL(timeout()), this, SLOT(trackC()));
    tC->start();

    lenxB = bon->x() - pac->x();
    lenyB = bon->y() - pac->y();
    pythB = sqrt(pow(lenxB, 2)+ pow(lenyB, 2));

    tB = new QTimer;
    tB->setInterval(10);
    connect(tB,SIGNAL(timeout()), this, SLOT(trackB()));
    tB->start();

    lenxF = fred->x() - pac->x();
    lenyF = fred->y() - pac->y();
    pythF = sqrt(pow(lenxF, 2)+ pow(lenyF, 2));

    tF = new QTimer;
    tF->setInterval(10);
    connect(tF,SIGNAL(timeout()), this, SLOT(trackF()));
    tF->start();

    tP = new QTimer(this);
    tP->setInterval(10);
    connect(tP, SIGNAL(timeout()), this, SLOT(trackPac()));
    tP->start();

    cB = new QTimer(this);
    cB->setInterval(500);
    connect(cB, SIGNAL(timeout()), this, SLOT(BonnieRun()));

    cC = new QTimer(this);
    cC->setInterval(500);
    connect(cC, SIGNAL(timeout()), this, SLOT(ChikaRun()));

    cF = new QTimer(this);
    cF->setInterval(500);
    connect(cF, SIGNAL(timeout()), this, SLOT(FreddyRun()));

    intro = Phonon::createPlayer(Phonon::MusicCategory, Phonon::MediaSource("D:/Werk/3de jaar/Semester 1/EERI 316/Menu/Audio/Night1.wav"));
    intro->play();

    go = new StartNight2();
    go->hide();
}

void Map::phase1()
{
    music->stop();
    music->play();
}

void Map::grid()
{
    flashInitialize();

    for(int i = 0; i < 40; i++)
    {
        for(int j = 0; j < 40; j++)
        {

            block = new QLabel(this);
            block->setFixedSize(50, 50);
            block->move(i*50, j*50);
            block->show();
            //Outer Walls
            if (i == 0 || j == 0 || i == 39 || j == 39)
            {
                block->setStyleSheet("background-color: rgb(30,30,30); border: 1px solid black;");

                canMove[i][j] = false;
                isWall[i][j] = true;
            }
            //Top left room
            else if ((j == 13 && (i==1||i==2||(i>=9&&i<=12))) || (i==12 && (j>0&&j<13)))
            {
                block->setStyleSheet("background-color: rgb(30,30,30); border: 1px solid black;");

                canMove[i][j] = false;
                isWall[i][j] = true;
            }
            //Middle left room
            else if (((j==17||j==23) && (i>0&&i<=9)) || (i==9&&(j==18||j==22)))
            {
                block->setStyleSheet("background-color: rgb(30,30,30); border: 1px solid black;");

                canMove[i][j] = false;
                isWall[i][j] = true;
            }
            //Bottom left Room
            else if ((j==27&&(i>=4&&i<=9))||(i==9&&(j>=28&&j<=38)))
            {
                block->setStyleSheet("background-color: rgb(30,30,30); border: 1px solid black;");

                canMove[i][j] = false;
                isWall[i][j] = true;
            }
            //Top center room
            else if ((i==16&&(j==1||(j>=5&&j<=8))) || (i==22&&j>0&&j<=8) || (j==8&&i>=17&&i<=21))
            {
                block->setStyleSheet("background-color: rgb(30,30,30); border: 1px solid black;");

                canMove[i][j] = false;
                isWall[i][j] = true;
            }
            //Center Room
            else if ((j==12&&i>=16&&i<=27) || (i==27&&j>=13&&j<=25) || (j==25&&i>=14&&i<=26) || (i==14&&j>=17&&j<=25) || (i==15&&j==17))
            {
                block->setStyleSheet("background-color: rgb(30,30,30); border: 1px solid black;");

                canMove[i][j] = false;
                isWall[i][j] = true;
            }
            // Bottom Center (Safe Room)
            else if (((i==14||i==25) && ((j>=29&&j<=32) || j>=36)) || (j==29&&i>=14&&i<=25))
            {
                block->setStyleSheet("background-color: rgb(30,30,30); border: 1px solid black;");

                canMove[i][j] = false;
                isWall[i][j] = true;
            }
            //Top right two rooms
            else if ((i==26 && j>0&&j<=8) || (j==8&&((i>=26&&i<=31) || i>=34)) || ((i==31||i==34) && (j>=3 && j<=8)))
            {
                block->setStyleSheet("background-color: rgb(30,30,30); border: 1px solid black;");

                canMove[i][j] = false;
                isWall[i][j] = true;
            }
            //Bottom right big room
            else if ((i==30&&j>=12&&j<=35) || (j==12&&i>=31) || (j==19&&i>=31&&i<=35) || (j==30&&((i>=31&&i<=32) || i>=36)))
            {
                block->setStyleSheet("background-color: rgb(30,30,30); border: 1px solid black;");

                canMove[i][j] = false;
                isWall[i][j] = true;
            }
            else
            {
                block->setStyleSheet("background-color: black");
                block->hide();

                canMove[i][j] = true;
                isWall[i][j] = false;
            }


        }//inside for
    }//outside for

    curtain = new QLabel(this);
    curtain->setFixedSize(50*11, 50*3);
    curtain->move(50,50);
    curtain->setStyleSheet("background-color: rgb(150, 0, 0);");
    //curtain->show();
    for(int i = 1; i <= 11; i++)
    {
        for(int j = 1; j<= 3; j++)
        {
            canMove[i][j] = false;
        }
    }

    tables[0] = new QLabel(this);
    QPixmap p(":/decor/decor/BlueTable.png");
    tables[0]->setPixmap(p);
    tables[0]->setFixedSize(p.width(), p.height());
    tables[0]->setStyleSheet("background-color: transparent;");
    tables[0]->move(22*50, 15*50);
    //tables[0]->show();
    for(int i = 22; i <= 24; i++)
    {
        for(int j = 15; j<= 17; j++)
        {
            canMove[i][j] = false;
        }
    }

    tables[1] = new QLabel(this);
    QPixmap p1(":/decor/decor/YellowTable.png");
    tables[1]->setPixmap(p1);
    tables[1]->setFixedSize(p1.width(), p1.height());
    tables[1]->setStyleSheet("background-color: transparent;");
    tables[1]->move(17*50, 20*50);
    //tables[1]->show();
    for(int i = 17; i <= 19; i++)
    {
        for(int j = 20; j<= 22; j++)
        {
            canMove[i][j] = false;
        }
    }

    tables[2] = new QLabel(this);
    QPixmap p2(":/decor/decor/RedTable.png");
    tables[2]->setPixmap(p2);
    tables[2]->setFixedSize(p2.width(), p2.height());
    tables[2]->setStyleSheet("background-color: transparent;");
    tables[2]->move(22*50, 20*50);
    //tables[2]->show();
    for(int i = 22; i <= 24; i++)
    {
        for(int j = 20; j<= 22; j++)
        {
            canMove[i][j] = false;
        }
    }

    tables[3] = new QLabel(this);
    tables[3]->setStyleSheet("background-color: rgb(128, 58, 8); border: 3px solid rgb(78, 24, 8);");;
    tables[3]->setFixedSize(150, 6*50);
    tables[3]->move(3*50, 31*50);
    //tables[3]->show();
    for(int i = 3; i <= 5; i++)
    {
        for(int j = 31; j<= 36; j++)
        {
            canMove[i][j] = false;
        }
    }

    tables[4] = new QLabel(this);
    tables[4]->setStyleSheet("background-color: rgb(237, 28, 36); border: 3px solid rgb(193, 0, 0);");;
    tables[4]->setFixedSize(6*50, 2*50);
    tables[4]->move(17*50, 30*50);
    //tables[4]->show();
    for(int i = 17; i <= 22; i++)
    {
        for(int j = 30; j<= 31; j++)
        {
            canMove[i][j] = false;
        }
    }

    tables[5] = new QLabel(this);
    QPixmap p5(":/decor/decor/CornerTable.png");
    tables[5]->setPixmap(p5);
    tables[5]->setFixedSize(p5.width(), p5.height());
    tables[5]->setStyleSheet("background-color: transparent;");
    tables[5]->move(36*50, 36*50);
    //tables[5]->show();
    for(int i = 36; i <= 38; i++)
    {
        for(int j = 36; j<= 38; j++)
        {
            canMove[i][j] = false;
        }
    }
    canMove[36][36] = true;
    canMove[37][36] = true;
    canMove[36][37] = true;


    tables[6] = new QLabel(this);
    tables[6]->setStyleSheet("background-color: rgb(60, 20, 0); border: 3px solid rgb(60, 20, 0);");;
    tables[6]->setFixedSize(2*50, 10*50);
    tables[6]->move(31*50, 20*50);
    //tables[6]->show();
    for(int i = 31; i <= 32; i++)
    {
        for(int j = 20; j<= 29; j++)
        {
            canMove[i][j] = false;
        }
    }

    tables[7] = new QLabel(this);
    tables[7]->setStyleSheet("background-color: rgb(60, 20, 0); border: 3px solid rgb(60, 20, 0);");;
    tables[7]->setFixedSize(3*50, 2*50);
    tables[7]->move(33*50, 20*50);
    //tables[7]->show();
    for(int i = 33; i <= 35; i++)
    {
        for(int j = 20; j<= 21; j++)
        {
            canMove[i][j] = false;
        }
    }

    tables[8] = new QLabel(this);
    tables[8]->setStyleSheet("background-color: rgb(148, 138, 84); border: 3px solid rgb(74, 69, 42);");;
    tables[8]->setFixedSize(8*50, 50);
    tables[8]->move(31*50, 13*50);
    //tables[8]->show();
    for(int i = 31; i <= 38; i++)
    {
            canMove[i][13] = false;
    }

    tables[9] = new QLabel(this);
    tables[9]->setStyleSheet("background-color: rgb(148, 138, 84); border: 3px solid rgb(74, 69, 42);");;
    tables[9]->setFixedSize(5*50, 50);
    tables[9]->move(31*50, 18*50);
    //tables[9]->show();
    for(int i = 31; i <= 35; i++)
    {
            canMove[i][18] = false;
    }

    for(int k =0; k <= 10; k++)
    {
        checkPoints[k] = new QLabel(this);
        checkPoints[k]->setStyleSheet("background-color: red;");
        checkPoints[k]->setFixedSize(50, 50);
        checkPoints[k]->show();
    }
    checkPoints[0]->move(8*50, 38*50);
    checkPoints[1]->move(50, 20*50);
    checkPoints[2]->move(15*50, 24*50);
    checkPoints[3]->move(26*50, 24*50);
    checkPoints[4]->move(26*50, 13*50);
    checkPoints[5]->move(21*50, 7*50);
    checkPoints[6]->move(27*50, 7*50);
    checkPoints[7]->move(38*50, 7*50);
    checkPoints[8]->move(31*50, 15*50);
    checkPoints[9]->move(38*50, 29*50);
    checkPoints[10]->move(38*50, 31*50);

}

void Map::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
    {
        this->close();
    }

    if(e->key() == Qt::Key_Down)
    {
        this->scroll(0, -50);
        scrollY -= 50;
    }

    if(e->key() == Qt::Key_Up)
    {
        this->scroll(0, 50);
        scrollY += 50;
    }

    if(e->key() == Qt::Key_Left)
    {
        this->scroll(50, 0);
        scrollX += 50;
    }

    if(e->key() == Qt::Key_Right)
    {
        this->scroll(-50, 0);
        scrollX -= 50;
    }

    if(e->key() == Qt::Key_W)
    {
        up = true;
        left = right = down = false;

        tm->start();
    }
    if(e->key() == Qt::Key_A)
    {
        left = true;
        up = right = down = false;

        tm->start();
    }
    if(e->key() == Qt::Key_S)
    {
        down = true;
        left = right = up = false;

        tm->start();
    }
    if(e->key() == Qt::Key_D)
    {
        right = true;
        left = up = down = false;

        tm->start();
    }

    if (e->key() == Qt::Key_Shift)
    {
        if (sprint == false)
        {
            sprint = true;
        }
        else
        {
            sprint = false;
        }
        setSpeed(sprint);

    }

    if(e->key() == Qt::Key_F)
    {
        if (flash == false)
        {
            flash = true;
        }
        else
        {
            flash = false;
            bon->hide();
            chik->hide();
            fred->hide();
        }
    }
}

void Map::MoveDirect()
{
    flashLight();

    if (left)
    {
        int checkX = (pac->x() - scrollX - 2)/50;
        int checkY = (pac->y() - scrollY)/50;

        if(canMove[checkX][checkY] == true && canMove[checkX][checkY+1] == true)
        {
            pac->move(pac->x()-speed, pac->y());
            lenxB = bon->x() - pac->x();
            lenxC = chik->x() - pac->x();
            lenxF = fred->x() - pac->x();
        }


        if(mouth >= flapspeed && open == true)
        {
            QPixmap pix(":/pacman/pacman3.png");
            pac->setPixmap(pix);
            pac->setFixedSize(pix.width(), pix.height());
            open = false;
            mouth = 0;
        }
        else if(mouth >= flapspeed && open == false)
        {
            QPixmap pix(":/pacman/pacman4.png");
            pac->setPixmap(pix);
            pac->setFixedSize(pix.width(), pix.height());
            open = true;
            mouth = 0;
        }
        else
        {
            mouth++;
        }

        if(pac->x() - bon->x() <= 350 && pac->x()-bon->x() >= 0 && (pac->y() - bon->y() <= 75 && bon->y() - pac->y() <= 75)  && pythB < 400  && flash == true && chaseB == false && soundB == true)
        {
            fright->stop();
            fright->play();
            bon->show();
            chaseB = true;
            soundB = false;
            cB->start();
        }
        if(pac->x() - chik->x() <= 350 && pac->x()-chik->x() >= 0 && (pac->y() - chik->y() <= 75 && chik->y() - pac->y() <= 75)  && pythC < 400  && flash == true && chaseC == false  && soundC == true)
        {
            fright->stop();
            fright->play();
            chik->show();
            chaseC = true;
            soundC = false;
            cC->start();

        }
        if(pac->x() - fred->x() <= 350 && pac->x()-fred->x() >= 0 && (pac->y() - fred->y() <= 75 && fred->y() - pac->y() <= 75)  && pythF < 400  && flash == true && chaseF == false && soundF == true)
        {
            fright->stop();
            fright->play();
            chik->show();
            chaseF = true;
            soundF = false;
            cF->start();
        }

    }

    if (right)
    {
        int checkX = (pac->x() - scrollX + 2)/50;
        int checkY = (pac->y() - scrollY)/50;

        if(canMove[checkX + 1][checkY + 1] == true && canMove[checkX + 1][checkY] == true)
        {
            pac->move(pac->x()+speed, pac->y());
            lenxB = bon->x() - pac->x();
            lenxC = chik->x() - pac->x();
            lenxF = fred->x() - pac->x();
        }

        if(mouth >= flapspeed && open == true)
        {
            QPixmap pix(":/pacman/pacman2.png");
            pac->setPixmap(pix);
            pac->setFixedSize(pix.width(), pix.height());
            open = false;
            mouth = 0;
        }
        else if(mouth >= flapspeed && open == false)
        {
            QPixmap pix(":/pacman/pacman1.png");
            pac->setPixmap(pix);
            pac->setFixedSize(pix.width(), pix.height());
            open = true;
            mouth = 0;
        }
        else
        {
            mouth++;
        }

        if(bon->x() - pac->x() <= 350 && bon->x()-pac->x() >= 0 && (pac->y() - bon->y() <= 75 && bon->y() - pac->y() <= 75)  && pythB < 400  && flash == true && chaseB == false  && soundB == true)
        {
            fright->stop();
            fright->play();
            bon->show();
            chaseB = true;
            soundB = false;
            cB->start();
        }
        if(chik->x() - pac->x() <= 350 && chik->x()-pac->x() >= 0 && (pac->y() - chik->y() <= 75 && chik->y() - pac->y() <= 75)  && pythC < 400  && flash == true && chaseC == false  && soundC == true)
        {
            fright->stop();
            fright->play();
            chik->show();
            chaseC = true;
            soundC = false;
            cC->start();
        }
        if(fred->x() - pac->x() <= 350 && fred->x()-pac->x() >= 0 && (pac->y() - fred->y() <= 75 && fred->y() - pac->y() <= 75)  && pythF < 400  && flash == true && chaseF == false  && soundF == true)
        {
            fright->stop();
            fright->play();
            fred->show();
            chaseF = true;
            soundF = false;
            cF->start();
        }
    }

    if (up)
    {

        int checkX = (pac->x() - scrollX)/50;
        int checkY = (pac->y() - scrollY - 2)/50;

        if(canMove[checkX][checkY] == true && canMove[checkX+1][checkY] == true)
        {
            pac->move(pac->x(), pac->y()-speed);
            lenyB = bon->y() - pac->y();
            lenyC = chik->y() - pac->y();
            lenyF = fred->y() - pac->y();
        }

        if(mouth >= flapspeed && open == true)
        {
            QPixmap pix(":/pacman/pacman5.png");
            pac->setPixmap(pix);
            pac->setFixedSize(pix.width(), pix.height());
            open = false;
            mouth = 0;
        }
        else if(mouth >= flapspeed && open == false)
        {
            QPixmap pix(":/pacman/pacman6.png");
            pac->setPixmap(pix);
            pac->setFixedSize(pix.width(), pix.height());
            open = true;
            mouth = 0;
        }
        else
        {
            mouth++;
        }

        if(pac->y() - bon->y() <= 350 && pac->y()-bon->y() >= 0 && (pac->x() - bon->x() <= 75 && bon->x() - pac->x() <= 75)  && pythB < 400  && flash == true && chaseB == false && soundB == true)
        {
            fright->stop();
            fright->play();
            bon->show();
            chaseB = true;
            soundB = false;
            cB->start();
        }
        if(pac->y() - chik->y() <= 350 && pac->y()-chik->y() >= 0 && (pac->x() - chik->x() <= 75 && chik->x() - pac->x() <= 75)  && pythC < 400  && flash == true && chaseC == false && soundC == true)
        {
            fright->stop();
            fright->play();
            chik->show();
            chaseC = true;
            soundC = false;
            cC->start();
        }

        if(pac->y() - fred->y() <= 350 && pac->y()-fred->y() >= 0 && (pac->x() - fred->x() <= 75 && fred->x() - pac->x() <= 75)  && pythF < 400  && flash == true && chaseF == false && soundF == true)
        {
            fright->stop();
            fright->play();
            fred->show();
            chaseF = true;
            soundF = false;
            cF->start();
        }
    }

    if (down)
    {
        int checkX = (pac->x() - scrollX)/50;
        int checkY = (pac->y() - scrollY + 2)/50;

        if(canMove[checkX + 1][checkY + 1] == true && canMove[checkX][checkY + 1] == true)
        {
            pac->move(pac->x(), pac->y()+speed);
            lenyB = bon->y() - pac->y();
            lenyC = chik->y() - pac->y();
            lenyF = fred->y() - pac->y();
        }

        if(mouth >= flapspeed && open == true)
        {
            QPixmap pix(":/pacman/pacman7.png");
            pac->setPixmap(pix);
            pac->setFixedSize(pix.width(), pix.height());
            open = false;
            mouth = 0;
        }
        else if(mouth >= flapspeed && open == false)
        {
            QPixmap pix(":/pacman/pacman8.png");
            pac->setPixmap(pix);
            pac->setFixedSize(pix.width(), pix.height());
            open = true;
            mouth = 0;
        }
        else
        {
            mouth++;
        }

        if(bon->y() - pac->y() <= 350 && bon->y()-pac->y() >= 0 && (pac->x() - bon->x() <= 75 && bon->x() - pac->x() <= 75) && pythB < 400 && flash == true && chaseB == false && soundB == true)
        {
            fright->stop();
            fright->play();
            bon->show();
            chaseB = true;
            soundB = false;
            cB->start();
        }
        if(chik->y() - pac->y() <= 350 && chik->y()-pac->y() >= 0 && (pac->x() - chik->x() <= 75 && chik->x() - pac->x() <= 75) && pythC < 400 && flash == true && chaseC == false && soundC == true)
        {
            fright->stop();
            fright->play();
            chik->show();
            chaseC = true;
            soundC = false;
            cC->start();
        }
        if(fred->y() - pac->y() <= 350 && fred->y()-pac->y() >= 0 && (pac->x() - fred->x() <= 75 && fred->x() - pac->x() <= 75) && pythF < 400 && flash == true && chaseF == false && soundF == true)
        {
            fright->stop();
            fright->play();
            fred->show();
            chaseF = true;
            soundF = false;
            cF->start();
        }


    }

}

void Map::setSpeed(bool s)
{
    if (s == false)
    {
        tm->setInterval(20);
    }
    else
    {
        tm->setInterval(10);
    }
}

void Map::trackB()
{

     pythB = sqrt(pow(lenxB, 2)+ pow(lenyB, 2));

     if (pythB < 400 && chaseB == false)
     {
    //-------------------left----------------------------
    if(pac->x()< bon->x())
    {
        int checkX = (bon->x() - scrollX -1)/50;
        int checkY = (bon->y() - scrollY)/50;

        if((canMove[checkX][checkY] == true && canMove[checkX][checkY+1] == true) && (checkX != 25 || checkY <= 29))
        {
             bon->move(pac->x()+ lenxB, bon->y());
             lenxB = lenxB -1;
        }
    }
    //--------------------top--------------------------
    if(pac->y() < bon->y())
    {
        int checkX = (bon->x() - scrollX)/50;
        int checkY = (bon->y() - scrollY - 1)/50;

        if(canMove[checkX][checkY] == true && canMove[checkX+1][checkY] == true)
        {
             bon->move(bon->x(), pac->y()+ lenyB);
             lenyB = lenyB -1;
        }
    }
    //-------------------Bottom-------------------------
    if(pac->y() > bon->y())
    {
        int checkX = (bon->x() - scrollX)/50;
        int checkY = (bon->y() - scrollY + 1)/50;

        if(canMove[checkX + 1][checkY + 1] == true && canMove[checkX][checkY + 1] == true)
        {
            bon->move(bon->x(), pac->y()+ lenyB);
            lenyB = lenyB + 1;
        }

    }
    //--------------------Right-----------------------
    if(pac->x()> bon->x())
    {
        int checkX = (bon->x() - scrollX + 1)/50;
        int checkY = (bon->y() - scrollY)/50;

        if(canMove[checkX + 1][checkY + 1] == true && canMove[checkX + 1][checkY] == true  && (checkX != 13 || checkY <= 29))
        {
            bon->move(pac->x()+ lenxB, bon->y());
            lenxB = lenxB + 1;
        }
    }
    //----------------------Caught------------------------------
    if(bon->x() == pac->x() && bon->y() == pac->y())
    {
         music->stop();
         tB->stop();
         this->close();
         scare1->Bonnie();;
         scare1->show();
         tm->stop();
    }
    }
     else if(chaseB == false)
     {
        soundB = true;
        bon->hide();
     }

}

void Map::trackC()
{

     pythC = sqrt(pow(lenxC, 2)+ pow(lenyC, 2));


     if (pythC < 400 && chaseC == false)
     {
    //-------------------left----------------------------
    if(pac->x()< chik->x())
    {
        int checkX = (chik->x() - scrollX -1)/50;
        int checkY = (chik->y() - scrollY)/50;

        if(canMove[checkX][checkY] == true && canMove[checkX][checkY+1] == true && (checkX != 25 || checkY <= 29))
        {
             chik->move(pac->x()+ lenxC, chik->y());
             lenxC = lenxC -1;
        }
    }
    //--------------------top--------------------------
    if(pac->y() < chik->y())
    {
        int checkX = (chik->x() - scrollX)/50;
        int checkY = (chik->y() - scrollY - 1)/50;

        if(canMove[checkX][checkY] == true && canMove[checkX+1][checkY] == true)
        {
             chik->move(chik->x(), pac->y()+ lenyC);
             lenyC = lenyC -1;
        }
    }
    //-------------------Bottom-------------------------
    if(pac->y() > chik->y())
    {
        int checkX = (chik->x() - scrollX)/50;
        int checkY = (chik->y() - scrollY + 1)/50;

        if(canMove[checkX + 1][checkY + 1] == true && canMove[checkX][checkY + 1] == true)
        {
            chik->move(chik->x(), pac->y()+ lenyC);
            lenyC = lenyC + 1;
        }

    }
    //--------------------Right-----------------------
    if(pac->x()> chik->x())
    {
        int checkX = (chik->x() - scrollX + 1)/50;
        int checkY = (chik->y() - scrollY)/50;

        if(canMove[checkX + 1][checkY + 1] == true && canMove[checkX + 1][checkY] == true && (checkX != 13 || checkY <= 29))
        {
            chik->move(pac->x()+ lenxC, chik->y());
            lenxC = lenxC + 1;
            //qDebug() << pythC;
        }
    }
    //----------------------Caught------------------------------
    if(chik->x() == pac->x() && chik->y() == pac->y())
    {
         music->stop();
         tC->stop();
         this->close();
         scare2->Chika();
         scare2->show();
         tm->stop();
    }
    }
     else if(chaseC == false)
     {
        soundC = true;
        chik->hide();

     }

}

void Map::trackF()
{

     pythF = sqrt(pow(lenxF, 2)+ pow(lenyF, 2));


     if (pythF < 400 && chaseF == false)
     {
    //-------------------left----------------------------
    if(pac->x()< fred->x())
    {
        int checkX = (fred->x() - scrollX -1)/50;
        int checkY = (fred->y() - scrollY)/50;

        if(canMove[checkX][checkY] == true && canMove[checkX][checkY+1] == true && (checkX != 25 || checkY <= 29))
        {
             fred->move(pac->x()+ lenxF, fred->y());
             lenxF = lenxF -1;
        }
    }
    //--------------------top--------------------------
    if(pac->y() < fred->y())
    {
        int checkX = (fred->x() - scrollX)/50;
        int checkY = (fred->y() - scrollY - 1)/50;

        if(canMove[checkX][checkY] == true && canMove[checkX+1][checkY] == true)
        {
             fred->move(fred->x(), pac->y()+ lenyF);
             lenyF = lenyF -1;
        }
    }
    //-------------------Bottom-------------------------
    if(pac->y() > fred->y())
    {
        int checkX = (fred->x() - scrollX)/50;
        int checkY = (fred->y() - scrollY + 1)/50;

        if(canMove[checkX + 1][checkY + 1] == true && canMove[checkX][checkY + 1] == true)
        {
            fred->move(fred->x(), pac->y()+ lenyF);
            lenyF = lenyF + 1;
        }

    }
    //--------------------Right-----------------------
    if(pac->x()> fred->x())
    {
        int checkX = (fred->x() - scrollX + 1)/50;
        int checkY = (fred->y() - scrollY)/50;

        if(canMove[checkX + 1][checkY + 1] == true && canMove[checkX + 1][checkY] == true && (checkX != 13 || checkY <= 29))
        {
            fred->move(pac->x()+ lenxF, fred->y());
            lenxF = lenxF + 1;
         }
    }
    //----------------------Caught------------------------------
    if(fred->x() == pac->x() && fred->y() == pac->y())
    {
         music->stop();
         tF->stop();
         this->close();
         scare->Freddy();
         scare->show();
         tm->stop();
         //vid1->play(freddy->currentSource());
    }
    }
     else if(chaseF == false)
     {
        soundF = true;
        fred->hide();
     }

}

void Map::addScares()
{/*
    freddy = new Phonon::MediaObject();
    //freddy->setCurrentSource(Phonon::MediaSource(QString("D:/Werk/3de jaar/Semester 1/EERI 316/Menu/vids/Freddy.mp4")));

    //setup player
    //
    vid1 = new Phonon::VideoPlayer(this);
    vid1->setFixedSize(QSize(1920,1080));
    vid1->move(0,0);
    vid1->show();
    connect(freddy, SIGNAL(finished()), freddy, SLOT(deleteLater()));
*/
}

void Map::trackPac()
{
    int i = (pac->x() - scrollX)/50;
    int j = (pac->y() - scrollY)/50;

    if (j <= 13 && i <= 12)
    {
        curtain->show();
    }

     //Bottom left Room
     else if (j>=27&&i<=9)
     {
        tables[3]->show();
     }

     //Center Room
     else if (j>=12 && i<=27 && j<=25 && i>=15)
     {
        tables[0]->show();
        tables[1]->show();
        tables[2]->show();
     }
     // Bottom Center (Safe Room)
     else if (i>=14 && i<=25 && j>=29)
     {
        tables[4]->show();
     }

     //Bottom right big room
     else if (i>=30 && j>=12)
     {
        tables[ 5]->show();
        tables[6]->show();
        tables[7]->show();
        tables[8]->show();
        tables[9]->show();
     }
     else
     {
         curtain->hide();
         for(int k = 0; k<=9; k++)
         {
             tables[k]->hide();
         }
     }

     if((i == 8 || i == 7) && (j == 38 || j == 37))
     {
         checkPoints[0]->setStyleSheet("background-color: green;");
         checked[0] = true;
     }
     else if(i == 1 && j == 20)
     {
         checkPoints[1]->setStyleSheet("background-color: green;");
         checked[1] = true;
     }
     else if(i == 15 && (j == 24 || j == 23))
     {
         checkPoints[2]->setStyleSheet("background-color: green;");
         checked[2] = true;
     }
     else if((i == 26 || i == 25) && (j == 24 || j == 23))
     {
         checkPoints[3]->setStyleSheet("background-color: green;");
         checked[3] = true;
     }
     else if((i == 26 || i == 25) && j == 13)
     {
         checkPoints[4]->setStyleSheet("background-color: green;");
         checked[4] = true;
     }
     else if((i == 21 || i == 20) && (j == 7 || j == 6))
     {
         checkPoints[5]->setStyleSheet("background-color: green;");
         checked[5] = true;
     }
     else if(i == 27 && (j == 7 || j == 6))
     {
         checkPoints[6]->setStyleSheet("background-color: green;");
         checked[6] = true;
     }
     else if((i == 38 || i == 37) && (j == 7 || j == 6))
     {
         checkPoints[7]->setStyleSheet("background-color: green;");
         checked[7] = true;
     }
     else if(i == 31 && j == 15)
     {
         checkPoints[8]->setStyleSheet("background-color: green;");
         checked[8] = true;
     }
     else if((i == 38 || i == 37) && (j == 29 || j == 28))
     {
         checkPoints[9]->setStyleSheet("background-color: green;");
         checked[9] = true;
     }
     else if((i == 38 || i == 37) && j == 31)
     {
         checkPoints[10]->setStyleSheet("background-color: green;");
         checked[10] = true;
     }

     if(checked[0] == true && checked[1] == true && checked[2] == true && checked[3] == true && checked[4] == true && checked[5] == true && checked[6] == true && checked[7] == true && checked[8] == true && checked[9] == true && checked[10] == true)
     {
         go->playVid();
         go->show();
         tP->stop();
         this->close();
     }
}

void Map::flashInitialize()
{
    for(int k = 0; k <= 7; k++)
    {
        light[k] = new QLabel(this);
        light[k]->hide();
    }

}

void Map::flashLight()
{
    int i = pac->x();
    int j = pac->y();

    if(flash)
    {
        //What to show
        for(int k = 0; k <= 7; k++)
        {
            light[k]->show();
        }

        QPixmap p(":/flashlight/Flashlight/flash1.png");

        QPixmap p1(":/flashlight/Flashlight/flash2.png");

        QPixmap p2(":/flashlight/Flashlight/flash3.png");

        QPixmap p3(":/flashlight/Flashlight/flash4.png");

        QPixmap p4(":/flashlight/Flashlight/flash5.png");

        QPixmap p5(":/flashlight/Flashlight/flash6.png");

        QPixmap p6(":/flashlight/Flashlight/flash7.png");

        QPixmap p7(":/flashlight/Flashlight/flash8.png");

        //Placement
        if(up)
        {
            light[0]->setPixmap(p);
            light[0]->setFixedSize(p.width(), p.height());

            light[1]->setPixmap(p1);
            light[1]->setFixedSize(p1.width(), p1.height());

            light[2]->setPixmap(p2);
            light[2]->setFixedSize(p2.width(), p2.height());

            light[3]->setPixmap(p3);
            light[3]->setFixedSize(p3.width(), p3.height());

            light[4]->setPixmap(p4);
            light[4]->setFixedSize(p4.width(), p4.height());

            light[5]->setPixmap(p5);
            light[5]->setFixedSize(p5.width(), p5.height());

            light[6]->setPixmap(p6);
            light[6]->setFixedSize(p6.width(), p6.height());

            light[7]->setPixmap(p7);
            light[7]->setFixedSize(p7.width(), p7.height());


            light[0]->move(i - 50, j - 50);
            light[1]->move(i - 50, light[0]->y() - light[1]->height());
            light[2]->move(i - 50, light[1]->y() - light[2]->height());
            light[3]->move(i - 50, light[2]->y() - light[3]->height());
            light[4]->move(i - 50, light[3]->y() - light[4]->height());
            light[5]->move(i - 50, light[4]->y() - light[5]->height());
            light[6]->move(i - 50, light[5]->y() - light[6]->height());
            light[7]->move(i - 50, light[6]->y() - light[7]->height());

            int checkX = (light[0]->x() + 75 - scrollX)/50;
            int checkY = (light[0]->y() +40 - scrollY)/50;

            if(isWall[checkX][checkY])
            {
                for(int k = 0; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[1]->y() +40 - scrollY)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 1; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[2]->y() +40 - scrollY)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 2; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[2]->y() +40 - scrollY)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 2; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[3]->y() +40 - scrollY)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 3; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[4]->y() +40 - scrollY)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 4; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[5]->y() +40 - scrollY)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 5; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[6]->y() +40 - scrollY)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 6; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[7]->y() +40 - scrollY)/50;
            if(isWall[checkX][checkY])
            {

                    light[7]->hide();

            }
        }

        if(down)
        {
            QTransform transform;
            QTransform trans = transform.rotate(180);
            QPixmap pd(p.transformed(trans));
            QPixmap p1d(p1.transformed(trans));
            QPixmap p2d(p2.transformed(trans));
            QPixmap p3d(p3.transformed(trans));
            QPixmap p4d(p4.transformed(trans));
            QPixmap p5d(p5.transformed(trans));
            QPixmap p6d(p6.transformed(trans));
            QPixmap p7d(p7.transformed(trans));

            light[0]->setPixmap(pd);
            light[0]->setFixedSize(pd.width(), pd.height());

            light[1]->setPixmap(p1d);
            light[1]->setFixedSize(p1d.width(), p1d.height());

            light[2]->setPixmap(p2d);
            light[2]->setFixedSize(p2d.width(), p2d.height());

            light[3]->setPixmap(p3d);
            light[3]->setFixedSize(p3d.width(), p3d.height());

            light[4]->setPixmap(p4d);
            light[4]->setFixedSize(p4d.width(), p4d.height());

            light[5]->setPixmap(p5d);
            light[5]->setFixedSize(p5d.width(), p5d.height());

            light[6]->setPixmap(p6d);
            light[6]->setFixedSize(p6d.width(), p6d.height());

            light[7]->setPixmap(p7d);
            light[7]->setFixedSize(p7d.width(), p7d.height());

            light[0]->move(i - 50, j + 50);
            light[1]->move(i - 50, light[0]->y() + light[1]->height());
            light[2]->move(i - 50, light[1]->y() + light[2]->height());
            light[3]->move(i - 50, light[2]->y() + light[3]->height());
            light[4]->move(i - 50, light[3]->y() + light[4]->height());
            light[5]->move(i - 50, light[4]->y() + light[5]->height());
            light[6]->move(i - 50, light[5]->y() + light[6]->height());
            light[7]->move(i - 50, light[6]->y() + light[7]->height());

            int checkX = (light[0]->x() + 75 - scrollX)/50;
            int checkY = (light[0]->y() - scrollY)/50;

            if(isWall[checkX][checkY])
            {
                for(int k = 0; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[1]->y() - scrollY)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 1; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[2]->y() - scrollY)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 2; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[2]->y() - scrollY)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 2; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[3]->y() - scrollY)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 3; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[4]->y() - scrollY)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 4; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[5]->y() - scrollY)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 5; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[6]->y() - scrollY)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 6; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkY = (light[7]->y() - scrollY)/50;
            if(isWall[checkX][checkY])
            {

                    light[7]->hide();

            }

        }

        if(left)
        {
            QTransform transform;
            QTransform trans = transform.rotate(270);
            QPixmap pd(p.transformed(trans));
            QPixmap p1d(p1.transformed(trans));
            QPixmap p2d(p2.transformed(trans));
            QPixmap p3d(p3.transformed(trans));
            QPixmap p4d(p4.transformed(trans));
            QPixmap p5d(p5.transformed(trans));
            QPixmap p6d(p6.transformed(trans));
            QPixmap p7d(p7.transformed(trans));

            light[0]->setPixmap(pd);
            light[0]->setFixedSize(pd.width(), pd.height());

            light[1]->setPixmap(p1d);
            light[1]->setFixedSize(p1d.width(), p1d.height());

            light[2]->setPixmap(p2d);
            light[2]->setFixedSize(p2d.width(), p2d.height());

            light[3]->setPixmap(p3d);
            light[3]->setFixedSize(p3d.width(), p3d.height());

            light[4]->setPixmap(p4d);
            light[4]->setFixedSize(p4d.width(), p4d.height());

            light[5]->setPixmap(p5d);
            light[5]->setFixedSize(p5d.width(), p5d.height());

            light[6]->setPixmap(p6d);
            light[6]->setFixedSize(p6d.width(), p6d.height());

            light[7]->setPixmap(p7d);
            light[7]->setFixedSize(p7d.width(), p7d.height());

            light[0]->move(i - light[0]->width(), j - 50);
            light[1]->move(light[0]->x() - light[1]->width(), j - 50);
            light[2]->move(light[1]->x() - light[2]->width(), j - 50);
            light[3]->move(light[2]->x() - light[3]->width(), j - 50);
            light[4]->move(light[3]->x() - light[4]->width(), j - 50);
            light[5]->move(light[4]->x() - light[5]->width(), j - 50);
            light[6]->move(light[5]->x() - light[6]->width(), j - 50);
            light[7]->move(light[6]->x() - light[7]->width(), j - 50);


            int checkX = (light[0]->x() + 40 - scrollX)/50;
            int checkY = (light[0]->y() + 75 - scrollY)/50;

            if(isWall[checkX][checkY])
            {
                for(int k = 0; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkX = (light[1]->x() + 40 - scrollX)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 1; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkX = (light[2]->x() + 40 - scrollX)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 2; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkX = (light[3]->x() + 40 - scrollX)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 3; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkX = (light[4]->x() + 40 - scrollX)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 4; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkX = (light[5]->x() + 40 - scrollX)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 5; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkX = (light[6]->x() + 40 - scrollX)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 6; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkX = (light[7]->x() + 40 - scrollX)/50;
            if(isWall[checkX][checkY])
            {

                light[7]->hide();

            }
        }

        if(right)
        {
            QTransform transform;
            QTransform trans = transform.rotate(90);
            QPixmap pd(p.transformed(trans));
            QPixmap p1d(p1.transformed(trans));
            QPixmap p2d(p2.transformed(trans));
            QPixmap p3d(p3.transformed(trans));
            QPixmap p4d(p4.transformed(trans));
            QPixmap p5d(p5.transformed(trans));
            QPixmap p6d(p6.transformed(trans));
            QPixmap p7d(p7.transformed(trans));

            light[0]->setPixmap(pd);
            light[0]->setFixedSize(pd.width(), pd.height());

            light[1]->setPixmap(p1d);
            light[1]->setFixedSize(p1d.width(), p1d.height());

            light[2]->setPixmap(p2d);
            light[2]->setFixedSize(p2d.width(), p2d.height());

            light[3]->setPixmap(p3d);
            light[3]->setFixedSize(p3d.width(), p3d.height());

            light[4]->setPixmap(p4d);
            light[4]->setFixedSize(p4d.width(), p4d.height());

            light[5]->setPixmap(p5d);
            light[5]->setFixedSize(p5d.width(), p5d.height());

            light[6]->setPixmap(p6d);
            light[6]->setFixedSize(p6d.width(), p6d.height());

            light[7]->setPixmap(p7d);
            light[7]->setFixedSize(p7d.width(), p7d.height());

            light[0]->move(i + 50, j - 50);
            light[1]->move(light[0]->x() + light[0]->width(), j - 50);
            light[2]->move(light[1]->x() + light[1]->width(), j - 50);
            light[3]->move(light[2]->x() + light[2]->width(), j - 50);
            light[4]->move(light[3]->x() + light[3]->width(), j - 50);
            light[5]->move(light[4]->x() + light[4]->width(), j - 50);
            light[6]->move(light[5]->x() + light[5]->width(), j - 50);
            light[7]->move(light[6]->x() + light[6]->width(), j - 50);

            int checkX = (light[0]->x() - scrollX)/50;
            int checkY = (light[0]->y() + 75 - scrollY)/50;

            if(isWall[checkX][checkY])
            {
                for(int k = 0; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkX = (light[1]->x() - scrollX)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 1; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkX = (light[2]->x() - scrollX)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 2; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkX = (light[3]->x() - scrollX)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 3; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkX = (light[4]->x() - scrollX)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 4; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkX = (light[5]->x() - scrollX)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 5; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkX = (light[6]->x() - scrollX)/50;
            if(isWall[checkX][checkY])
            {
                for(int k = 6; k <= 7; k++)
                {
                    light[k]->hide();
                }
            }
            checkX = (light[7]->x() - scrollX)/50;
            if(isWall[checkX][checkY])
            {

                light[7]->hide();

            }
        }

    }
    else
    {
        for(int k = 0; k <= 7; k++)
        {
            light[k]->hide();
        }
    }
}

void Map::BonnieRun()
{
    chaseB = false;
    cB->stop();
}

void Map::ChikaRun()
{
    chaseC = false;
    cC->stop();
}

void Map::FreddyRun()
{
    chaseF = false;
    cF->stop();
}


