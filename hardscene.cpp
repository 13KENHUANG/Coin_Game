#include "hardscene.h"

#define offSetValue 4
#define scene_W     800
#define scene_H     800
#define level_size  13
hardScene::hardScene(int level)
{
   // HardMusic->play();
    this->isWin = false;
    this->LV = level;
    this->setFixedSize(scene_W,scene_H);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻金幣場景(困難)");

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

    nextLabel = new QLabel;
    tmpPix.load(":/res/NEXT.PNG");
    tmpPix = tmpPix.scaled(QSize(241,84));
    nextLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    nextLabel->setPixmap(tmpPix);
    nextLabel->setParent(this);
    nextLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());

    //設置backBtn
    connect(backBtn,&MyPushButton::clicked,[=](){
        //  qDebug()<<"click back";
        //  延時返回
        backSound->play();
        QTimer::singleShot(200,this,[=](){
            emit this->hardSceneBack();
        });
    });

    //設置hintBtn
    connect(hintBtn,&MyPushButton::clicked,[=](){
        hintSound->play();
        hintBtn->zoom3();
        HintMsg(LV);
      //  myhint = Simulate(this->gameArray);
    });

    int offset_x = (scene_H-(level_size)*50)/2;


    //for(int i=0;i<this->LV+offSetValue;i++)
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
            label->move(offset_x+j*50,offset_x+i*50);
            myLabel[i][j] = label;

            QString str;
            if(this->gameArray[i][j]==1)
                str = ":/res/Coin0001.png";
            else
                str = ":/res/Coin0008.png";
            mycoin *coin = new mycoin(str);
            coin->setParent(this);
            coin->move(offset_x+2+j*50,offset_x+4+i*50);
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
    Reset_Level(this->LV);
    Timer_500ms = startTimer(500);
}

int hardScene::LVconvert(int LV)
{
    int count = 0;
    switch (LV) {
    case 0:
        count = 5;
        break;
    case 1:
        count = 7;
        break;
    case 2:
        count = 9;
        break;
    case 3:
        count = 11;
        break;
    case 4:
        count = 13;
        break;
    default:
        break;
    }
    return count;
}

void hardScene::Reset_Level(int LV)
{
    int count = LVconvert(LV);
    int offset = (level_size - count)/2;
    int offend = (count+offset-1);
    /*
    LV = 0 , count = 5 , offset = 4 , offend = 8
    LV = 1 , count = 7 , offset = 3 , offend = 9
    LV = 2 , count = 9 , offset = 2 , offend = 10
    LV = 3 , count = 11, offset = 1 , offend = 11
    LV = 4 , count = 13, offset = 0 , offend = 12
    */
    for(int i=0;i<level_size;i++)
    {
        for(int j=0;j<level_size;j++)
        {
            if(i>=offset && i<=offend &&
               j>=offset && j<=offend)
            {
                coinBtn[i][j]->show();
                myLabel[i][j]->show();
                if(coinBtn[i][j]->flag==true)
                {
                    coinBtn[i][j]->changeFlag();
                }
            }
            else
            {
                coinBtn[i][j]->hide();
                myLabel[i][j]->hide();
            }
        }
    }


}

void hardScene::HintMsg(int LV)
{
    QString str;
    switch (LV) {
    case 0:
        str = "              11000               ";
        break;
    case 1:
        str = "             1101011              ";
        break;
    case 2:
        str = "            000000000             ";
        break;
    case 3:
        str = "           10001000000            ";
        break;
    case 4:
        str = "          1101011101011           ";
        break;
    default:
        break;
    }
    QMessageBox::information(this,"Hint",str);
}

bool hardScene::Check_Win(int LV)
{
   // qDebug()<<"checking";
    int count  = LVconvert(LV);
    int offset = (level_size-count)/2;
    int offend = (count+offset-1);

    for(int i=0;i<level_size;i++)
    {
        for(int j=0;j<level_size;j++)
        {
            if(i>=offset && i<= offend &&
               j>=offset && j<= offend)
            {
                if(coinBtn[i][j]->flag==false)
                {
                    return false;
                }
            }
            else
            {
                continue;
            }
        }
    }
    return true;

}

void hardScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/hard_scene.PNG");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void hardScene::timerEvent(QTimerEvent *event)
{
    static bool tmp = false;
    if(event->timerId()==Timer_500ms)
    {
        if(Check_Win(this->LV))
        {
            qDebug()<<"wwww";
            if(this->LV<4)
            {
                qDebug()<<"I am here";
                nextLabel->show();
                QPropertyAnimation *NextA = new QPropertyAnimation(nextLabel,"geometry");
                //Set time
                NextA->setDuration(1000);
                //Set Start
                NextA->setStartValue(QRect(nextLabel->x(),nextLabel->y(),nextLabel->width(),nextLabel->height()));
                //Set End
                NextA->setEndValue(QRect(nextLabel->x(),nextLabel->y()+114,nextLabel->width(),nextLabel->height()));
                //Set Curve
                NextA->setEasingCurve(QEasingCurve::OutBounce);
                NextA->start();
                this->LV++;

                QTimer::singleShot(1500,this,[=](){
                    nextLabel->hide();
                    nextLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());

                    Reset_Level(LV);
                });
            }
            else
            {
                winSound->play();
                qDebug()<<"Win!!!!";
                for(int i=0;i<level_size;i++)
                {
                    for(int j=0;j<level_size;j++)
                    {
                        coinBtn[i][j]->isWin=true;
                    }
                }
                //Set Succes Picture
                if(!tmp)
                {
                QPropertyAnimation *SuccA = new QPropertyAnimation(winLabel,"geometry");
                //Set time
                SuccA->setDuration(1000);
                //Set Start
                SuccA->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                //Set End
                SuccA->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                //Set Curve
                SuccA->setEasingCurve(QEasingCurve::OutBounce);
                SuccA->start();
                QTimer::singleShot(1500,this,[=](){
                    SuccA->stop();
                });
                tmp = true;
                }
            }
        }

    }
}



