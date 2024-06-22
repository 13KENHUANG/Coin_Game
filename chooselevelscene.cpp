
#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QSound>

hardScene *hardplay = NULL;
ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    //設置大小
    this->setFixedSize(320,588);

    //設置圖標
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //設置標題
    this->setWindowTitle("Choose Level");

    //創建菜單欄
    QMenuBar *bar = menuBar();
    setMenuBar(bar);

    //創建開始菜單
    QMenu *startMenu = bar->addMenu("開始");

    //創建退出
    QAction *quitAction = startMenu->addAction("退出");

    //點擊退出 實現退出遊戲
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    QSound *chooseSound = new QSound(":/res/TapButtonSound.wav",this);
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    //返回按鈕
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //點擊返回
    connect(backBtn,&MyPushButton::clicked,[=](){
      //  qDebug()<<"click back";
      //  延時返回
       backSound->play();
       QTimer::singleShot(200,this,[=](){
          emit this->chooseSceneBack();
       });
    });


    //創建選擇關卡按鈕
    for(int i=0 ;i<20;i++)
    {
        MyPushButton *menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+i%4*70,130+i/4*70);


        //監聽每個按鈕的點擊事件
        connect(menuBtn,&MyPushButton::clicked,[=](){

            //播放音效
            chooseSound->play();

            QString str = QString("您選擇的是第 %1 關").arg(i+1);
            qDebug()<<str;

            //進入遊戲場景
            this->hide();
            play = new PlayScene(i+1);

            play->setGeometry(this->geometry());

            play->show();


            connect(play,&PlayScene::chooseSceneBack,[=](){
                this->setGeometry(play->geometry());
                QTimer::singleShot(300,this,[=](){
                    this->show();
                    delete play;
                    play = NULL;
                });


            });
        });


//      menuBtn->setText(QString::number(i+1)); 使用按鈕本身setText 效果較差
        QLabel *label = new QLabel;
        QFont font;
        font.setBold(true);
        font.setPointSize(16);

        label->setFont(font);
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);

        //設置Label上的文字對齊方式 水平居中 垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //label->setAlignment(Qt::AlignCenter); 跟上面同樣效果
        //設置讓鼠標進行穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }

    //創建困難模式
    MyPushButton *hardBtn = new MyPushButton(":/res/pink_btn.PNG","",0,130,50);
    hardBtn->setParent(this);
    hardBtn->move(this->width()*0.08,this->height()*0.84);
    //添加文字
    QLabel *label = new QLabel;
    QFont font;
    font.setBold(true);
    font.setPointSize(16);

    label->setFont(font);
    label->setParent(this);
    label->setFixedSize(hardBtn->width(),hardBtn->height());
    label->setText("Hard");
    label->move(this->width()*0.08,this->height()*0.84);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label->setAttribute(Qt::WA_TransparentForMouseEvents);


    //定義connect
    //定義按下hard_mode Btn
    connect(hardBtn,&MyPushButton::clicked,[=](){
        hardBtn->setEnabled(false);
        chooseSound->play();
        hardBtn->zoom3();
        QTimer::singleShot(200,this,[=]{
            hardplay = new hardScene(0);
            hardplay->setGeometry(this->geometry());
            this->hide();
            hardplay->show();

            //定義hard_mode中的back btn
            connect(hardplay, &hardScene::hardSceneBack,[=]{
                this->setGeometry(hardplay->geometry());
                QTimer::singleShot(100,this,[=]{
                    hardBtn->setEnabled(true);
                    this->show();
                    delete hardplay;
                    hardplay=NULL;
                });
            });
        });

    });



    //創建隨機模式
    MyPushButton *randomBtn = new MyPushButton(":/res/blue_btn.PNG","",0,130,50);
    randomBtn->setParent(this);
    randomBtn->move(this->width()*0.53,this->height()*0.84);
    QLabel *label2 = new QLabel;
    label2->setFont(font);
    label2->setParent(this);
    label2->setFixedSize(randomBtn->width(),randomBtn->height());
    label2->setText("Random");
    label2->move(this->width()*0.53,this->height()*0.84);
    label2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label2->setAttribute(Qt::WA_TransparentForMouseEvents);

}

void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    //加載背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加載標題
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix);
}

