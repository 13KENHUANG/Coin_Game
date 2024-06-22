
#include "mycoin.h"

//mycoin::mycoin(QWidget *parent)
//    : QPushButton{parent}
//{

//}


mycoin::mycoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret)
    {
        QString str = QString("圖片 %1 加載失敗").arg(btnImg);
        qDebug()<<str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));


    //initialize timer
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //1->0
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->min>this->max)
        {
            this->min=1;
            isAnimation=false;
            timer1->stop();
        }
    });


    //0->1
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->max<this->min)
        {
            this->max=8;
            isAnimation=false;
            timer2->stop();
        }
    });

}


//change 1->0, 0->1
void mycoin::changeFlag()
{
    //1->0
    if(this->flag)
    {
        timer1->start(30);
        isAnimation=true;
        this->flag = false;
    }

    //0->1
    else
    {
        timer2->start(30);
        isAnimation=true;
        this->flag = true;
    }
}

void mycoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation | this->isWin)
    {
        return;
    }
    else
        QPushButton::mousePressEvent(e);
}
