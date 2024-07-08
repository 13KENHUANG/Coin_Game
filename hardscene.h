#ifndef HARDSCENE_H
#define HARDSCENE_H

#include <QMainWindow>
#include <QMessageBox>
#include "mypushbutton.h"
#include "chooselevelscene.h"
#include "mycoin.h"



class hardScene:public QMainWindow
{
    Q_OBJECT
public:
    int LV = 0;
    int Timer_500ms;

    hardScene(int level);
    QPixmap tmpPix;

    int gameArray[13][13]={0};

    mycoin *coinBtn[13][13];
    QLabel *myLabel[13][13];
    QLabel *nextLabel;
    QLabel *winLabel;

    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    QSound *winSound  = new QSound(":/res/LevelWinSound.wav",this);
    QSound *hintSound = new QSound(":/res/TapButtonSound.wav",this);



    bool isWin;
    int Timer_1;
    int  LVconvert(int LV);
    void Reset_Level(int LV);
    void HintMsg(int LV);
    bool Check_Win(int LV);
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    bool tmp = false;
signals:
    void hardSceneBack();
    void changeLevel(int LV);

};

#endif // HARDSCENE_H
