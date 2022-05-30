#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>
//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}
//声明有默认参数 构造别加默认参数 否则会报找不到这个函数的调用的报错

MyPushButton::MyPushButton(QString normalImage,QString pressImage)
{
    this->normalImagPath=normalImage;
    this->pressImagPath=pressImage;
    QPixmap pix;

    //防止图片传入的路径不对 提前看有无错误
    bool ret=pix.load(this->normalImagPath);
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }

    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());

    //设置图片的不规则样式 将边框设置0像素 css
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标按钮的大小
    this->setIconSize(pix.size());

}

//实现按钮的向下跳动
void MyPushButton::zoom1()
{
    //创建动态对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");//限制这个对象在一个矩形内跳动

    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置 （Qrect是一个矩形 照应我上面写的在一个矩形内跳动）
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳时的曲线有一个小波浪形的感觉
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //开始执行动画
    animation->start();
}

//实现按钮的向上跳动
void MyPushButton::zoom2()
{
    //创建动态对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");//限制这个对象在一个矩形内跳动

    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置 （Qrect是一个矩形框 照应我上面写的在一个矩形内跳动）
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳时的曲线有一个小波浪形的感觉
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //开始执行动画
    animation->start();
}

//重写按钮的按下和释放事件 为back按钮做铺垫 按下和释放的时候显示两个不同的图片
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImagPath!="")
    {
        QPixmap pix;
        //防止图片传入的路径不对 提前看有无错误
        bool ret=pix.load(this->pressImagPath);//传入的图片中pressImagePath不为空 切换成按下后的图片
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置图片的不规则样式 将边框设置0像素 css
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标按钮的大小
        this->setIconSize(pix.size());
    }
    //让父类执行mousePressEvent中的其他内容
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImagPath!="")
    {
        QPixmap pix;
        //防止图片传入的路径不对 提前看有无错误
        bool ret=pix.load(this->normalImagPath);//传入的图片中pressImagePath不为空 切换成初始图片
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());

        //设置图片的不规则样式 将边框设置0像素 css
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标按钮的大小
        this->setIconSize(pix.size());

    }
    //让父类执行mouseReleaseEvent中的其他内容
    return QPushButton::mouseReleaseEvent(e);
}
