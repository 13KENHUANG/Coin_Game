#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H


#include <QPushButton>


class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);

    //構造函數
    MyPushButton(QString normalImg,QString pressImg="",int Img_type=0,int width=-1,int height=-1);

    //成員屬性
    QString normalImgPath;
    QString pressImgPath;

    int  img_flag = 0;

    //彈跳特效
    void zoom1(); //向下跳
    void zoom2(); //向上跳
    void zoom3();

    //重寫按鈕 按下 和 釋放
    void mousePressEvent(QMouseEvent *e);

    void mouseReleaseEvent(QMouseEvent *e);

    void enterEvent(QEvent *event);

    void leaveEvent(QEvent *);




signals:

   // int Img_type = 0;
    int Img_type();

};

#endif // MYPUSHBUTTON_H
