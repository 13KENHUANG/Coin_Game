
#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "chooselevelscene.h"
#include <QMouseEvent>




QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow

{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    //重寫paintEvent事件 畫背景圖
    void paintEvent(QPaintEvent *);

    ChooseLevelScene *chooseScene = NULL;


private:
    Ui::MainScene *ui;
};

#endif // MAINSCENE_H
