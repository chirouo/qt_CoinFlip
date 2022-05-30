#include "mycoin.h"
#include <QPixmap>
#include <QDebug>
//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

//重新写一个我自己的构造函数
//传入的参数表示是金币还是银币
MyCoin::MyCoin(QString coinImg)
{
    QPixmap pix;
    bool ret=pix.load(coinImg);
    if(!ret)
    {
        QString str=QString("图片 %1 加载失败").arg(coinImg);
        qDebug()<<str;
    }
    this->setFixedSize(pix.width(),pix.height());

    //设置金币无边框
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer_1=new QTimer(this);
    timer_2=new QTimer(this);

    //监听正面翻成反面的信号 并翻转金币
    connect(timer_1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->img_min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //if 判断金币是否翻完了 若翻完了 将min重置回1
        if(this->img_min>this->img_max)
        {
            img_min=1;
            this->timer_1->stop();
            this->isDoingAnimation=false;//翻转玩了 标示着动画做完了
        }
    });

    //监听反面翻成正面的信号 并翻转银币
    connect(timer_2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->img_max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //if 判断银币是否翻完了 若翻完了 将max重置回8
        if(this->img_max<this->img_min)
        {
            img_max=8;
            this->timer_2->stop();
            this->isDoingAnimation=false;//翻转玩了 标示着动画做完了
        }
    });
}


//重写鼠标按下的事件 如果isDoingAnimatio是true则不执行鼠标按下 等待动画做完才能执行
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isDoingAnimation||this->isWin_Coin)
    {
        return;
    }
    else
    {
        //剩下的交给父类处理
        QPushButton::mousePressEvent(e);
    }
}

//改变金币图片的判定方法
void MyCoin::changeFlag()
{
    //如果判定为正面 则向反面翻
    if(this->flag)
    {
        //开始正面翻反面的定时器
        timer_1->start(30);
        //将flag充值为反面 即0
        this->flag=false;
        this->isDoingAnimation=true;//正在做翻转的动画
    }
    else//反面翻正面
    {
        //开始反面翻正面的定时器
        timer_2->start(30);
        //将flag充值为正面 即1
        this->flag=true;
        this->isDoingAnimation=true;//正在做翻转的动画
    }
}
