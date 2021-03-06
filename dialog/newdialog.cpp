#include "newdialog.h"
#include <QString>
NewDialog::NewDialog(QWidget *parent) :
    QWidget(parent)
{
    QString* s;
    label = new QLabel(parent);
    label->move(328 + 25,247 -10);
    label->setMinimumSize(500,100);
    skillCount = 0;
    frame = new QPixmap();
    frame->load(":/character/chooseCharacterFrame.png");
    s = new QString(QString::fromUtf8("请选择响应"));
    font = new QFont();
    font->setPointSize(30);
    font->setBold(true);
    palette = new QPalette();
    palette->setColor(QPalette::WindowText,Qt::yellow);
    label->setPalette(*palette);
    label->setFont(*font);
    label->setText(*s);
    delete s;
}
void NewDialog::init(int chara)
{
    switch(chara)
    {
        case 1:
        {
            skillCount = 4;
            skillGroup[0] = new PicButton(54,328 + 25,479,100,42,false);
            skillGroup[1] = new PicButton(55,328 + 150,479,100,42,false);
            skillGroup[2] = new PicButton(56,328 + 275,479,100,42,false);
            skillGroup[3] = new PicButton(57,328 + 400,479,100,42,false);
            break;
        }
        case 2:
        {
            skillCount = 3;
            skillGroup[0] = new PicButton(58,328 + 25,479,100,42,false);
            skillGroup[1] = new PicButton(59,328 + 150,479,100,42,false);
            skillGroup[2] = new PicButton(60,328 + 275,479,100,42,false);
            break;
        }
        case 3:
        {
            skillCount = 2;
            skillGroup[0] = new PicButton(61,328 + 25,479,100,42,false);
            skillGroup[1] = new PicButton(63,328 + 150,479,100,42,false);
            break;
        }
        case 4:
        {
            skillCount = 1;
            skillGroup[0] = new PicButton(65,328 + 25,479,100,42,false);
            break;
        }
        case 5:
        {
            skillCount = 1;
            skillGroup[0] = new PicButton(69,328 + 25,479,100,42,false);
            break;
        }
        case 7:
        {
            skillCount = 2;
            skillGroup[0] = new PicButton(78,328 + 25,479,100,42,false);
            skillGroup[1] = new PicButton(79,328 + 150,479,100,42,false);
            break;
        }
        case 8:
        {
            skillCount = 1;
            skillGroup[0] = new PicButton(81,328 + 25,479,100,42,false);
            break;
        }
        case 9:
        {
            skillCount = 2;
            skillGroup[0] = new PicButton(83,328 + 25,479,100,42,false);
            skillGroup[1] = new PicButton(86,328 + 150,479,100,42,false);
            break;
        }
        case 10:
        {
            skillCount = 2;
            skillGroup[0] = new PicButton(89,328 + 25,479,100,42,false);
            skillGroup[1] = new PicButton(90,328 + 150,479,100,42,false);
            break;
        }
        case 13:
        {
            skillCount = 1;
            skillGroup[0] = new PicButton(101,328 + 25,479,100,42,false);
            break;
        }
        case 15:
        {
            skillCount = 1;
            skillGroup[0] = new PicButton(107,328 + 25,479,100,42,false);
            break;
        }
        case 16:
        {
            skillCount = 1;
            skillGroup[0] = new PicButton(118,328 + 25,479,100,42,false);
            break;
        }
        case 17:
        {
            skillCount = 1;
            skillGroup[0] = new PicButton(119,328 + 25,479,100,42,false);
            break;
        }
        case 18:
        {
            skillCount = 3;
            skillGroup[0] = new PicButton(124,328 + 25,479,100,42,false);
            skillGroup[1] = new PicButton(125,328 + 150,479,100,42,false);
            skillGroup[2] = new PicButton(126,328 + 275,479,100,42,false);
            break;
        }
        case 19:
        {
            skillCount = 5;
            skillGroup[0] = new PicButton(128,328 + 25,479 - 50,100,42,false);
            skillGroup[1] = new PicButton(129,328 + 25,479,100,42,false);
            skillGroup[2] = new PicButton(130,328 + 150,479,100,42,false);
            skillGroup[3] = new PicButton(131,328 + 275,479,100,42,false);
            skillGroup[4] = new PicButton(132,328 + 400,479,100,42,false);
            break;
        }
        case 20:
        {
            skillCount = 3;
            skillGroup[0] = new PicButton(133,328 + 25,479,100,42,false);
            skillGroup[1] = new PicButton(134,328 + 150,479,100,42,false);
            skillGroup[2] = new PicButton(136,328 + 275,479,100,42,false);
            break;
        }
        case 21:
        {
            skillCount = 4;
            skillGroup[0] = new PicButton(138,328 + 25,479,100,42,false);
            skillGroup[1] = new PicButton(139,328 + 150,479,100,42,false);
            skillGroup[2] = new PicButton(141,328 + 275,479,100,42,false);
            skillGroup[3] = new PicButton(142,328 + 400,479,100,42,false);
            break;
        }
        case 22:
        {
            skillCount = 3;
            skillGroup[0] = new PicButton(144,328 + 25,479,100,42,false);
            skillGroup[1] = new PicButton(145,328 + 150,479,100,42,false);
            skillGroup[2] = new PicButton(149,328 + 275,479,100,42,false);
            break;
        }
        case 24:
        {
            skillCount = 4;
            skillGroup[0] = new PicButton(158,328 + 25,479,100,42,false);
            skillGroup[1] = new PicButton(159,328 + 150,479,100,42,false);
            skillGroup[2] = new PicButton(160,328 + 275,479,100,42,false);
            skillGroup[3] = new PicButton(161,328 + 400,479,100,42,false);
            break;
        }
        case 101:
        {
            skillCount = 10;
            for(int i = 0;i < 3;i++)
            {
                skillGroup[i] = new PicButton(200 + i,328 + 25 + 125 * i,479 - 150,100,42,false);
            }
            for(int i = 3;i < 7;i++)
            {
                skillGroup[i] = new PicButton(200 + i,328 + 25 + 125 * (i - 3),479 - 90,100,42,false);
            }
            for(int i = 7;i < 10;i++)
            {
                skillGroup[i] = new PicButton(200 + i,328 + 25 + 125 * (i - 7),479 - 30,100,42,false);
            }
            break;
        }
    }
}
void NewDialog::set(bool canX[])
{
    for(int i = 0;i < skillCount;i++)
    {
        if(canX[i])
        {
            skillGroup[i]->canBeClicked = true;
        }
    }
}
void NewDialog::paint(QPaintEvent *event, QPainter *painter)
{
    painter->drawPixmap(328,247,frame->width(),frame->height(),*frame);
    for(int i = 0;i < skillCount;i++)
    {
        skillGroup[i]->paint(event,painter);
    }
    label->show();
}
