#ifndef CARDATTACK_H
#define CARDATTACK_H

#include <QWidget>
#include <QPixmap>
#include "cardbutton.h"
#include "cardList.h"
class CardAttack : public QWidget
{
    Q_OBJECT
public:
    CardList* cardList;
    explicit CardAttack(QWidget *parent);
    QPixmap* card;
    QWidget* window;
    void set(int infomation[15]);
    int cardCount;
    int cardDiscardCount;
    CardButton* cardDiscard[8];
    int discardXp;
    int discardYp;
    int cardDiscardNum[8];
    int initialXp;
    int initialYp;
    int endXp[6];
    int endYp[6];
    double angle[6];
    int detaX[6];
    int detaY[6];
    int frameCount;
    int overPaint;
    bool self;
    bool onlyself;
    bool over[6];
    bool paintOverX;
    bool paintEnd;
    double paintAngle[6];
    void paint(QPaintEvent*,QPainter*);
    int setCoordinateX(int site);
    int setCoordinateY(int site);
    void destroyPic();
signals:
    void paintOver();
public slots:

};

#endif // CARDATTACK_H
