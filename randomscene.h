#ifndef RANDOMSCENE_H
#define RANDOMSCENE_H

#include <QMainWindow>
#include <QMessageBox>
#include "mypushbutton.h"
#include "chooselevelscene.h"
#include "mycoin.h"
#include <ctime>

#define row 6
#define col 6
class randomscene:public QMainWindow
{
    Q_OBJECT
public:

    int gameArray[row][col]={0};
    mycoin *coinBtn[row][col];
    QLabel *myLabel[row][col];

    randomscene();

    QLabel *winLabel;

    QPixmap tmpPix;

    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    QSound *winSound  = new QSound(":/res/LevelWinSound.wav",this);
    QSound *hintSound = new QSound(":/res/TapButtonSound.wav",this);

    bool isWin;

    void paintEvent(QPaintEvent *event);
    void HintMsg();
    void fillArrayWithRandom();
    bool ArrayHasAns(int Array[][]);


signals:
    void randomSceneBack();


};

#endif // RANDOMSCENE_H
