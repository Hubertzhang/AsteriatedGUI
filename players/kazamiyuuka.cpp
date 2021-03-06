#include "kazamiyuuka.h"

KazamiYuuka::KazamiYuuka(PaintStruct* paintStruct,QWidget *parent) :
    CardAndSkill(paintStruct,parent)
{
    YuukaTwoCount = 0;
    ask = false;
    dialog = new NewDialog(windowX);
    dialog->init(20);//蓄力一击,念弹,苍炎之魂
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
}
void KazamiYuuka::changeSelfMode(int mode)
{
    cancel->canBeClicked = true;
    disconnect(ensure,SIGNAL(changeClicked()),this,SLOT(selfReset()));
    switch(mode)
    {
        case 4://蓄力一击响应阶段
        case 6://苍炎之魂响应阶段
        {
            emit resetSignal();
            break;
        }
        case 5://念弹响应阶段
        {
            clickRivalSet();
            break;
        }
        case 7://YuukaOne;
        {
            informationKind = 300;
            clickRivalSet();
            break;
        }
        case 8://YuukaTwo;
        {
            informationKind = 301;
            if(paintStructX->gameCharacter[5]->cardNum < 4)
            {
                cancel->canBeClicked = false;
                sendMessageSelf();
            }
            else
            {
                for(int i = 0;i < cardNum;i++)
                {
                    cardButton[i]->canBeClicked = true;
                    connect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(YuukaTwoPlus()));
                    connect(cardButton[i],SIGNAL(notClicked()),this,SLOT(YuukaTwoMinus()));
                }
            }
        }
    }
}
void KazamiYuuka::paint(QPaintEvent *event, QPainter *painter)
{
    if(ask)
    {
        dialog->paint(event,painter);
    }
    ensure->paint(event,painter);
    cancel->paint(event,painter);
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->paint(event,painter);
    }
}
void KazamiYuuka::setFrame()
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
void KazamiYuuka::skillCancel()
{
    ask = false;
    YuukaTwoCount = 0;
    dialog->label->hide();
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->canBeClicked = true;
        disconnect(cardButton[i],SIGNAL(changeClicked()),this,SLOT(YuukaTwoPlus()));
        disconnect(cardButton[i],SIGNAL(notClicked()),this,SLOT(YuukaTwoMinus()));
    }
}
void KazamiYuuka::selfReset()
{
    //system("pause");
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isClicked)
        {
            changeSelfMode(4 + i);
        }
    }
    dialogReset();
}
void KazamiYuuka::dialogReset()
{
    dialog->label->hide();
    ask = false;
    for(int i = 0;i < dialog->skillCount;i++)
    {
        dialog->skillGroup[i]->canBeClicked = false;
        dialog->skillGroup[i]->isClicked = false;
    }
}
void KazamiYuuka::dialogSet(bool canX[])
{
    dialog->set(canX);
}
void KazamiYuuka::sendMessageSelf()
{
    for(int i = 0;i < dialog->skillCount;i++)
    {
        if(dialog->skillGroup[i]->isClicked)
        {
            informationKind = 100 + i;
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
        case 100://蓄力一击响应阶段
        case 102://苍炎之魂响应阶段
        {
            tempMes.push_back(informationKind - 99);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 101:
        {
            for(int i = 0;i < 6;i++)
            {
                if(paintStructX->gameCharacter[i]->characterPic->isClicked)
                {
                    putCharacter(tempMes);
                    emit sendMessageSelfSig(tempMes);
                    return;
                }
            }
            tempMes.push_back(2);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 300://YuukaOne
        {
            putCharacter(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        case 301://YuukaTwo
        {
            putCardCount(tempMes);
            putCard(tempMes);
            emit sendMessageSelfSig(tempMes);
            return;
        }
        default:
        {
            sendMessageIn();
        }
    }
}
void KazamiYuuka::YuukaTwoPlus()
{
    YuukaTwoCount ++;
    if(YuukaTwoCount == paintStructX->gameCharacter[5]->cardNum - 3)
    {
        for(int i = 0;i < cardNum;i++)
        {
            if(!cardButton[i]->isClicked)
            {
                cardButton[i]->canBeClicked = false;
            }
        }
        ensure->canBeClicked = true;
    }
}
void KazamiYuuka::YuukaTwoMinus()
{
    YuukaTwoCount --;
    ensure->canBeClicked = false;
    for(int i = 0;i < cardNum;i++)
    {
        cardButton[i]->canBeClicked = true;
    }
}
void KazamiYuuka::YuukaOne()
{
    changeSelfMode(7);
}
void KazamiYuuka::YuukaTwo()
{
    changeSelfMode(8);
}
