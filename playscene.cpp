
#include "playscene.h"



PlayScene::PlayScene(int levelNum)
{
    this->isWin=false;
    QString str = QString("進入第 %1 關").arg(levelNum);
    qDebug()<<str;
    this->levelIndex = levelNum;

    //初始化遊戲場景
    //設置固定大小
    this->setFixedSize(320,588);
    //設置圖標
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //設置標題
    this->setWindowTitle("翻金幣場景");

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

    //返回按鈕
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");

    //音效設置
    QSound *backSound = new QSound(":/res/BackButtonSound.wav",this);
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    QSound *winSound  = new QSound(":/res/LevelWinSound.wav",this);

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

    //顯示當前關卡
    QLabel *label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setBold(true);
   // font.setFamily("華文新魏");
    font.setPointSize(20);
    QString str1 = QString("Level :%1").arg(this->levelIndex);
    //將字體設置到標籤控建中
    label->setFont(font);
    label->setText(str1);
//    label->setGeometry(30,this->height()-50,120,50);
    label->setGeometry(200,30,120,50);


    dataConfig config;
    //初始化每個關卡的二維數組
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }

    QLabel *winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());

    failLabel = new QLabel;
    tmpPix.load(":/res/Fail.PNG");
    tmpPix = tmpPix.scaled(QSize(241,84));
    failLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    failLabel->setPixmap(tmpPix);
    failLabel->setParent(this);
    failLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());

    //顯示金幣背景圖案
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QPixmap pix = QPixmap(":/res/BoardNode.png");
            QLabel *label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57+j*50,200+i*50);

            //創建金幣
            //---test----
           // cout<<this->gameArray[i][j]<<",";
            QString str;
            if(this->gameArray[i][j]==1)
            {
                str = ":/res/Coin0001.png";
            }
            else
            {
                str = ":/res/Coin0008.png";
            }
            mycoin *coin = new mycoin(str);
            coin->setParent(this);
            coin->move(59+j*50,204+i*50);

            //給金幣屬性
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];

            //將金幣放入到金幣的二維數組中
            coinBtn[i][j]=coin;

            connect(coin,&mycoin::clicked,[=](){
                flipSound->play();

                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        this->coinBtn[i][j]->isWin=true;
                    }
                }
                coin->changeFlag();
                this->gameArray[i][j]=this->gameArray[i][j]==1?0:1;

                //翻轉周圍金幣,延時翻轉
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<=3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY]==1?0:1;
                    }
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY]==1?0:1;
                    }
                    if(coin->posY+1<=3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1]==1?0:1;
                    }
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1]==1?0:1;
                    }

                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            this->coinBtn[i][j]->isWin=false;
                        }
                    }
                    //判斷勝利
                    this->isWin=true;
                    for(int i=0;i<4&&isWin;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinBtn[i][j]->flag==false)
                            {
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    //is Win!!!
                    if(this->isWin)
                    {
                        winSound->play();
                        qDebug()<<"Win!!!!";
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinBtn[i][j]->isWin=true;
                            }
                        }
                        //Set Succes Picture
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
                    }


                });


            });


        }
        //cout<<endl;
    }


    //=========Add by Ken=========
    QFont myFont;
    Timer_1 = startTimer(1000);

    myFont.setPointSize(16);
    myFont.setBold(true);

    myEdit = new QLineEdit;
    myEdit->setParent(this);

    myEdit->setFont(myFont);
    myEdit->setAlignment(Qt::AlignCenter);
    myEdit->setStyleSheet("QLineEdit { border: 3px solid black; }");

    QString mystr = "倒數計時："+QString::number(Limit_Time)+"s";
    myEdit->setText(mystr);
    myEdit->setGeometry(0,this->height()-50,200,50);
 //   myEdit->setStyleSheet("QLineEdit { background: transparent; }");


    //============================
}

void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/K_mormal_mode__.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //畫背景左上圖標
    pix.load(":/res/Title.png");

    //pix = pix.scaled( pix.width()*0.5 , pix.height()*0.5);

    painter.drawPixmap(10,30,pix.width()*0.5 , pix.height()*0.5,pix);
}

void PlayScene::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==Timer_1 && !isWin)
    {
        Limit_Time--;
        QString mystr = "倒數計時："+QString::number(Limit_Time)+"s";
        myEdit->setText(mystr);
        if(Limit_Time==0)
        {
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                {
                    coinBtn[i][j]->isWin=true;
                }
            }
            killTimer(Timer_1);
            //Set Succes Picture
            QPropertyAnimation *SuccA = new QPropertyAnimation(failLabel,"geometry");
            //Set time
            SuccA->setDuration(1000);
            //Set Start
            SuccA->setStartValue(QRect(failLabel->x(),failLabel->y(),failLabel->width(),failLabel->height()));
            //Set End
            SuccA->setEndValue(QRect(failLabel->x(),failLabel->y()+124,failLabel->width(),failLabel->height()));
            //Set Curve
            SuccA->setEasingCurve(QEasingCurve::OutBounce);
            SuccA->start();

        }
    }

}
