
#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H


#include <QMainWindow>
#include <QWidget>
#include "playscene.h"
#include "hardscene.h"
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //繪圖事件
    void paintEvent(QPaintEvent *);

    //遊戲場景對象指針

    PlayScene * play = NULL;
//    hardScene *hardplay = NULL;



signals:
    //寫一個自定義的信號 告訴主場景 點擊了返回
    void chooseSceneBack();

};

#endif // CHOOSELEVELSCENE_H
