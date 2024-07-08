#include "randomscene.h"


#define scene_W     400
#define scene_H     600
#define level_size  6

randomscene::randomscene()
{
    this->isWin = false;
    this->setFixedSize(scene_W,scene_H);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻金幣場景(隨機)");

    QMenuBar *bar = menuBar();
    setMenuBar(bar);
    QMenu *startMenu = bar->addMenu("開始");
    QAction *quitAction = startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //設置退回按鈕
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //設置提示按鈕
    MyPushButton *hintBtn = new MyPushButton(":/res/HINT.PNG","",0,100,40);
    hintBtn->setParent(this);
    hintBtn->move(this->width()-(110),20);

    winLabel = new QLabel;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());

    //設置backBtn
    connect(backBtn,&MyPushButton::clicked,[=](){
        //  qDebug()<<"click back";
        //  延時返回
        backSound->play();
        QTimer::singleShot(200,this,[=](){
            emit this->randomSceneBack();
        });
    });

    //設置hintBtn
    connect(hintBtn,&MyPushButton::clicked,[=](){
        hintSound->play();
        hintBtn->zoom3();
        HintMsg();
      //  myhint = Simulate(this->gameArray);
    });

    //計算金幣擺放的位置數據
    int offset_x = (scene_W-(level_size)*50)/2;
    int offset_y = (scene_H-(level_size)*50)/2;

    //打亂數組
    fillArrayWithRandom();

    //設置金幣配置
    for(int i=0;i<level_size;i++)
    {
//        for(int j=0;j<this->LV+offSetValue;j++)
        for(int j=0;j<level_size;j++)
        {
            QPixmap pix = QPixmap(":/res/BoardNode.png");
            QLabel *label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(offset_x+j*50,offset_y+i*50);
            myLabel[i][j] = label;

            QString str;
            if(this->gameArray[i][j]==1)
                str = ":/res/Coin0001.png";
            else
                str = ":/res/Coin0008.png";
            mycoin *coin = new mycoin(str);
            coin->setParent(this);
            coin->move(offset_x+2+j*50,offset_y+4+i*50);
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];
            coinBtn[i][j]=coin;

            connect(coin,&mycoin::clicked,[=](){
                flipSound->play();

                //金幣動作時，不能點其他金幣
                for(int i=0;i<level_size;i++)
                {
                    for(int j=0;j<level_size;j++)
                    {
                        this->coinBtn[i][j]->isWin=true;
                    }
                }
                coin->changeFlag();
                this->gameArray[i][j]=this->gameArray[i][j]==1?0:1;

                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<=level_size-1)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY]==1?0:1;
                    }
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY]==1?0:1;
                    }
                    if(coin->posY+1<=level_size-1)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1]==1?0:1;
                    }
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1]==1?0:1;
                    }

                    for(int i=0;i<level_size;i++)
                    {
                        for(int j=0;j<level_size;j++)
                        {
                            this->coinBtn[i][j]->isWin=false;
                        }
                    }
            });

        });
       }
    }
}

void randomscene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/random_scene.PNG");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void randomscene::HintMsg()
{

}

void randomscene::fillArrayWithRandom()
{
    std::srand(std::time(0));

    for(int i=0 ; i<6 ; i++)
    {
        for(int j=0 ;j<6 ;j++)
            this->gameArray[i][j] = std::rand() % 2;
    }
}
