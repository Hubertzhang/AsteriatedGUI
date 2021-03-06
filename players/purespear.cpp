#include "purespear.h"

PureSpear::PureSpear(PaintStruct* paintStruct,QWidget *parent,Window* groundX) :
    CardAndSkill(paintStruct,parent)
{
    ask = false;
    spearAsk = false;
    dialog = new NewDialog(windowX);
    dialog->init(10);//天枪,地枪
    int info[3] = {2,0,0};
    groundSpear = new AskDialog(info,groundX,paintStructX,false);
    groundSpear->ensure->canBeClicked = false;
    groundSpear->cancel->canBeClicked = false;
    groundSpear->ensure->isClicked = false;
    groundSpear->cancel->isClicked = false;
    for(int i = 0;i < 5;i++)
    {
        groundSpear->number[i]->isClicked = false;
        groundSpear->number[i]->canBeClicked = false;
    }
    connect(groundSpear->ensure,SIGNAL(changeClicked()),this,SLOT(sendMessageCardAndSkill()));
    connect(groundSpear->cancel,SIGNAL(changeClicked()),this,SLOT(sendMessageCardAndSkill()));
    disconnect(groundSpear->ensure,SIGNAL(changeClicked()),groundSpear,SLOT(destroyLabel()));
    disconnect(groundSpear->cancel,SIGNAL(changeClicked()),groundSpear,SLOT(destroyLabel()));
    connect(groundSpear->ensure,SIGNAL(changeClicked()),this,SLOT(reset()));
    connect(groundSpear->cancel,SIGNAL(changeClicked()),this,SLOT(reset()));
    magicGroup[0] = new PicButton(87,362,559,100,42,false);
    magicGroup[1] = new PicButton(88,465,559,100,42,false);
    magicGroup[2] = new PicButton(91,568,559,100,42,false);
    for(int i = 0;i < dialog->skillCount;i++)
    {
        for(int j = 0;j < dialog->skillCount;j++)
        {
            if(i != j)
            {
                connect(dialog->skillGroup[i],SIGNAL(changeClicked()),dialog->skillGroup[j],SLOT(cancelX()));
            }
        }
        connect(dialog->skillGroup[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(dialog->skillGroup[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        connect(this,SIGNAL(mouseClick(int,int)),dialog->skillGroup[i],SLOT(isThisClicked(int,int)));
    }
    for(int i = 0;i < 3;i++)
    {
        connect(this,SIGNAL(mouseClick(int,int)),magicGroup[i],SLOT(isThisClicked(int,int)));
    }
    for(int i = 0;i < 3;i++)
    {
        for(int j = 0;j < 3;j++)
        {
            if(i != j)
            {
                connect(magicGroup[i],SIGNAL(changeClicked()),magicGroup[j],SLOT(cancelX()));
            }
        }
    }
    //system("pause");
    connect(magicGroup[0],SIGNAL(changeClicked()),this,SLOT(magicSetZero()));
    connect(magicGroup[1],SIGNAL(changeClicked()),this,SLOT(magicSetOne()));
    connect(magicGroup[2],SIGNAL(changeClicked()),this,SLOT(magicSetTwo()));
    for(int i = 0;i < 3;i++)
    {
        connect(magicGroup[i],SIGNAL(notClicked()),this,SLOT(skillClear()));
    }
}
void PureSpear::magicSetZero()
{
    linkReset();
    skillset();
    changeSelfMode(4);
    magicGroup[0]->isClicked = true;
}
void PureSpear::magicSetOne()
{
    linkReset();
    skillset();
    //system("pause");
    changeSelfMode(5);
    magicGroup[1]->isClicked = true;
}
void PureSpear::magicSetTwo()
{
    linkReset();
    skillset();
    ensure->canBeClicked = true;
    //system("pause");
    magicGroup[2]->isClicked = true;
}
void PureSpear::changeSelfMode(int mode)
{
    for(int i = 0;i < cardNum;i++)
    {
        for(int j = 0;j < cardNum;j++)
        {
            if(i != j)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),cardButton[j],SLOT(cancelX()));
            }
        }
        for(int j = 0;j < 6;j++)
        {
            if(paintStructX->gameCharacter[5]->color != paintStructX->gameCharacter[j]->color)
            {
                connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                connect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
            }
        }
    }
    for(int i = 0;i < 6;i++)
    {
        connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
        connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
        for(int j = 0;j < 6;j ++)
        {
            if(i != j)
            {
                connect(paintStructX->gameCharacter[i]->characterPic,SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelX()));
            }
        }
    }
    cancel->canBeClicked = true;
    switch(mode)
    {
        case 4://辉耀响应阶段
        {
            cancel->canBeClicked = false;
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getNature(card[i]) == water)
                {
                    cardButton[i]->canBeClicked = true;
                }
                for(int j = 0;j < 6;j++)
                {
                    if(paintStructX->gameCharacter[5]->color != paintStructX->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        disconnect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                }
                connect(cardButton[i],SIGNAL(changeClicked()),ensure,SLOT(recoverClick()));
                connect(cardButton[i],SIGNAL(notClicked()),ensure,SLOT(cancelClick()));
            }
            break;
        }
        case 5://惩戒响应阶段
        {
            cancel->canBeClicked = false;
            for(int i = 0;i < cardNum;i++)
            {
                if(cardList->getType(card[i]) == magic)
                {
                    cardButton[i]->canBeClicked = true;
                }
            }
            for(int i = 0;i < cardNum;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(paintStructX->gameCharacter[5]->color != paintStructX->gameCharacter[j]->color)
                    {
                        disconnect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        disconnect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                    if(paintStructX->gameCharacter[j]->cure && j!= 5)
                    {
                        connect(cardButton[i],SIGNAL(changeClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(recoverClick()));
                        connect(cardButton[i],SIGNAL(notClicked()),paintStructX->gameCharacter[j]->characterPic,SLOT(cancelClick()));
                    }
                }
            }
            break;
        }
        case 6://天枪响应阶段
        {
            emit resetSignal();
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }
        case 7://地枪响应阶段
        {
            spearAsk = true;
            groundSpear->ensure->canBeClicked = false;
            int cureUse = 4;
            if(cureUse > paintStructX->gameCharacter[5]->cure)
            {
                cureUse = paintStructX->gameCharacter[5]->cure;
            }
            for(int i = 0;i < 5;i++)
            {
                if(i < cureUse)
                {
                    groundSpear->number[i]->canBeClicked = true;
                }
                else
                {
                    groundSpear->number[i]->canBeClicked = false;
                }
            }
            disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
            break;
        }
    }
}
void PureSpear::paint(QPaintEvent *event, QPainter *painter)
{
    if(ask)
    {
        dialog->paint(event,painter);
    }
    if(spearAsk)
    {
        groundSpear->paint(event,painter);
    }
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->paint(event,painter);
    }
    ensure->paint(event,painter);
    cancel->paint(event,painter);
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->paint(event,painter);
    }
}
void PureSpear::setFrame()
{
    ask = true;
}
/*void SwordMaster::skillReset()
{
    cancelClick = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->isClicked = false;
    }
}*/
void PureSpear::skillset()
{
    for(int i = 0;i < cardNum;i++)
    {
        if(cardList->getNature(card[i]) == water)
        {
            magicGroup[0]->canBeClicked = true;
        }
        if(cardList->getType(card[i]) == magic)
        {
            magicGroup[1]->canBeClicked = true;
        }
    }
    if(paintStructX->gameCharacter[5]->gem!= 0)
    {
        magicGroup[2]->canBeClicked = true;
    }
}
void PureSpear::skillCancel()
{
    ask = false;
    spearAsk = false;
    groundSpear->labelOne->hide();
    groundSpear->labelTwo->hide();
    for(int i = 0;i < 3;i++)
    {
        magicGroup[i]->canBeClicked = false;
        magicGroup[i]->isClicked = false;
    }
    groundSpear->ensure->canBeClicked = false;
    groundSpear->cancel->canBeClicked = false;
    groundSpear->ensure->isClicked = false;
    groundSpear->cancel->isClicked = false;
    for(int i = 0;i < 5;i++)
    {
        groundSpear->number[i]->isClicked = false;
        groundSpear->number[i]->canBeClicked = false;
    }
}
void PureSpear::skillClear()
{
    int info[3] = {0,0,0};
    linkReset();
    changePaintMode(2,info);
}
void PureSpear::selfReset()
{
    //system("pause");
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isClicked)
        {
            changeSelfMode(6 + i);
        }
    }
    dialogReset();
}
void PureSpear::dialogReset()
{
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->canBeClicked = false;
        dialog->skillGroup[i]->isClicked = false;
    }
}
void PureSpear::dialogSet(bool canX[])
{
    dialog->set(canX);
}
void PureSpear::sendMessageSelf()
{
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isClicked)
        {
            informationKind = 100 + i;
        }
    }
    for(int i = 0;i < 3;i++)
    {
        if(magicGroup[i]->isClicked)
        {
            informationKind = 200 + i;
        }
    }
    std::vector<int> tempMes;
    if(cancel->isClicked && informationKind < 100)
    {
        if(informationKind == 7)
        {
            tempMes.push_back(-1);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        tempMes.push_back(0);
        emit sendMessageSelfSig(tempMes);
        return;
    }
    if(cancel->isClicked && informationKind > 99 && !ensure->canBeClicked)
    {
        tempMes.push_back(-1);
        emit sendMessageSelfSig(tempMes);
        return;
    }
    if(cancel->isClicked && informationKind > 99 && ensure->canBeClicked)
    {
        tempMes.push_back(0);
        emit sendMessageSelfSig(tempMes);
        return;
    }
    switch(informationKind)
    {
        case 100://天枪响应阶段
        {
            tempMes.push_back(3);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 101://地枪响应阶段
        {
        //system("pause");
            if(groundSpear->cancel->isClicked)
            {
                tempMes.push_back(-1);
                emit sendMessageSelfSig(tempMes);
                return;
            }
            for(int i = 0;i < 5;i++)
            {
                if(groundSpear->number[i]->isClicked)
                {
                    tempMes.push_back(i + 1);
                    emit sendMessageSelfSig(tempMes);
                    return;
                }
            }
            tempMes.push_back(4);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 200://辉耀响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(1);
            for(int i = 0;i < cardNum;i++)
            {
                if(cardButton[i]->isClicked)
                {
                    tempMes.push_back(card[i]);
                    emit sendMessageSelfSig(tempMes);
                    return;
                }
           }
        }
        case 201://惩戒响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(2);
            for(int i = 0;i < cardNum;i++)
            {
                if(cardButton[i]->isClicked)
                {
                    for(int j = 0;j < 6;j++)
                    {
                        if(paintStructX->gameCharacter[j]->characterPic->isClicked)
                        {
                            int site = (-j + paintStructX->yourSite + 5) % 6;
                            tempMes.push_back(site);
                            tempMes.push_back(card[i]);
                            emit sendMessageSelfSig(tempMes);
                            return;
                        }
                    }
                }
            }
        }
        case 202://圣光祈愈响应阶段
        {
            tempMes.push_back(1);
            tempMes.push_back(5);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        default:
        {
            sendMessageIn();
        }
    }
}
