#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImg, QString pressImg , int Img_type,int width,int height)
{
    //設置鼠標追蹤狀態
    setMouseTracking(true);

    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;
    this->img_flag = Img_type;
   // this->Img_type = Img_type;

    QPixmap pix;
    bool ret = pix.load(normalImg);
    if(width!=-1 && height !=-1)
    {
        pix = pix.scaled(QSize(width,height));
    }
    if(!ret)
    {
        qDebug()<<"圖片load失敗";
        return ;
    }
    //set img size
    this->setFixedSize(pix.width(),pix.height());

    //設置不規則圖片樣式
    this->setStyleSheet("QPushButton{border:0px}");

    //設置圖標
    this->setIcon(pix);

    //設置圖標大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyPushButton::zoom1()
{
    //創建動態對象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //設置動畫時間間隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //結束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //設置彈跳曲線
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //執行動畫
    animation->start();
}

void MyPushButton::zoom2()
{
    //創建動態對象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //設置動畫時間間隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //結束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //設置彈跳曲線
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //執行動畫
    animation->start();
}

void MyPushButton::zoom3()
{
    //創建動態對象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //設置動畫時間間隔
    animation->setDuration(150);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+5,this->width(),this->height()));
    //結束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //設置彈跳曲線
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //執行動畫
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath !="") //傳入的按下圖片不為空 說明需要有按下狀態
    {
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);
        if(!ret)
        {
            qDebug()<<"圖片load失敗";
            return ;
        }

        //set img size
        this->setFixedSize(pix.width(),pix.height());

        //設置不規則圖片樣式
        this->setStyleSheet("QPushButton{border:0px}");

        //設置圖標
        this->setIcon(pix);

        //設置圖標大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath !="") //傳入的按下圖片不為空 說明需要有按下狀態
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if(!ret)
        {
            qDebug()<<"圖片load失敗";
            return ;
        }

        //set img size
        this->setFixedSize(pix.width(),pix.height());

        //設置不規則圖片樣式
        this->setStyleSheet("QPushButton{border:0px}");

        //設置圖標
        this->setIcon(pix);

        //設置圖標大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}

void MyPushButton::enterEvent(QEvent *event)
{
    if(this->img_flag==1)
        qDebug()<<"鼠標進入了";
}

void MyPushButton::leaveEvent(QEvent *)
{
    if(this->img_flag==1)
       qDebug()<<"鼠標離開了";
}
