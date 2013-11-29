#ifndef ASKDIALOG_H
#define ASKDIALOG_H

#include <QWidget>
#include <QPainter>
#include <QString>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include "picbutton.h"
#include "paintstruct.h"
class Window;
class AskDialog : public QWidget
{
    Q_OBJECT
public:
    Window* storeWindow;
    QString s;
    QPixmap* bg;
    PicButton* ensure;
    PicButton* cancel;
    QFont* font;
    QLabel* labelOne;
    QLabel* labelTwo;
    QPalette* palette;
    PaintStruct* storeData;
    PicButton* attributeGroup[4];
    PicButton* activateGroup[2];
    PicButton* refineGroup[5];
    PicButton* buyGroup[3];
    PicButton* composeGroup[3];
    PicButton* number[5];
    int actNum;
    int getActivatedNum(int characterNum);
    void activeInit(int characterNum);
    void paint(QPaintEvent*,QPainter*);
    bool canActivate(int skillNum);
    explicit AskDialog(int information[3],Window *parent,PaintStruct*);
    ~AskDialog();
    int kind[3];
signals:

public slots:
    void destroyLabel();
};

#endif // ASKDIALOG_H
