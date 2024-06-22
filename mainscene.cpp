#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //設置視窗大小
    this->setFixedSize(320,588);
    //設置圖標圖片
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //標題
    this->setWindowTitle("Ken的翻金幣project");

    //退出
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //開始按鈕音效
    QSound *startSound = new QSound(":/res/TapButtonSound.wav",this);

    //設置-1->音效無限循環
    //startSound->setLoops(-1);

    //開始按鈕
//    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");

    //***把按鈕添加到畫面上***
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5 - startBtn->width()*0.5,this->height()*0.7);
    startBtn->img_flag=1;

    //實例化選擇關卡場景
    chooseScene = new ChooseLevelScene;

    //監聽選擇關卡的返回按鈕的信號
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
        this->setGeometry(chooseScene->geometry());
        chooseScene->hide();
        this->show();
    });

    connect(startBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"has click";

        //播放音效
        startSound->play();
        //做彈起特效
//        startBtn->zoom1();
        startBtn->zoom2();

        //延時進入選擇關卡場景
        QTimer::singleShot(200,this,[=](){
            //設置chooseScene 場景位置
            chooseScene->setGeometry(this->geometry());

            //進入選擇關卡場景中
            this->hide();
            chooseScene->show();
        });
    });
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/K_main_scene__2.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //畫背景左上圖標
    pix.load(":/res/K_title.PNG");

    //pix = pix.scaled( pix.width()*0.5 , pix.height()*0.5);

    painter.drawPixmap(this->width()/2-pix.width()*0.5*0.3 ,60,pix.width()*0.3 , pix.height()*0.3,pix);
}


MainScene::~MainScene()
{
    delete ui;
}




