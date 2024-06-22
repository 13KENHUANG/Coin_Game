
#ifndef MYCOIN_H
#define MYCOIN_H


#include <QPushButton>
#include <QTimer>
#include <QDebug>
class mycoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit mycoin(QWidget *parent = nullptr);
    //參數代表
    mycoin(QString btnImg);

    //金幣的屬性
    int posX;
    int posY;
    bool flag;

    //change coin
    void changeFlag();
    QTimer *timer1; //1->0
    QTimer *timer2; //0->1
    int min=1;
    int max=8;

    //執行動畫標誌
    bool isAnimation=false;

    //重寫按下
    void mousePressEvent(QMouseEvent *e);

    //當設置為true時,封鎖按鈕功能
    bool isWin=false;

signals:

};

#endif // MYCOIN_H
