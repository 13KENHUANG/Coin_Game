
#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QLabel>
#include <QMainWindow>
#include <QTimerEvent>
#include "mycoin.h"
#include <QLineEdit>
#include <QMenuBar>
#include <QPainter>
#include <QSound>
#include <QFont>
#include "mypushbutton.h"
#include <QTimer>
#include "dataconfig.h"
#include <QPropertyAnimation>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelNum);

    int levelIndex; //內部成員屬性

    int Limit_Time = 10;

    int Timer_1;

    //重寫painterEvent
    void paintEvent(QPaintEvent *event);

    int gameArray[4][4];

    mycoin *coinBtn[4][4];

    QLineEdit *myEdit;
    QLabel *failLabel;

    bool isWin;

    void timerEvent(QTimerEvent *event);
signals:
    void chooseSceneBack();

};

#endif // PLAYSCENE_H
