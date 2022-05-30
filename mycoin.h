#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCoin(QWidget *parent = nullptr);
    //重新写一个我自己的构造函数
    MyCoin(QString coinImg);

    //金币或者银币的属性
    int positionX;//x坐标
    int positionY;//y坐标
    bool flag;//判断正面还是反面

    //改变金币图片的判断方法
    void changeFlag();
    //提高代码可读性 写两个定时器
    QTimer *timer_1;//正面翻反面
    QTimer *timer_2;//反面翻正面
    int img_min=1;
    int img_max=8;

    //执行动画的标志
    bool isDoingAnimation=false;

    //重写鼠标按下的事件 如果isDoingAnimatio是true则不执行鼠标按下 等待动画做完才能执行
    void mousePressEvent(QMouseEvent *e);

    //coin自己的isWin
    bool isWin_Coin=false;
signals:

public slots:
};

#endif // MYCOIN_H
