#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include <QString>
#include <QPushButton>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:

//    explicit MyPushButton(QWidget *parent = nullptr);

    //自己写一个构造函数 参数1是正常的照片 参数二是按下按钮时的照片
    MyPushButton(QString normalImage,QString pressImage="");

    //两个成员属性保护传入的两个照片路径
     QString normalImagPath;
     QString pressImagPath;

     //实现按钮的向下跳动
     void zoom1();

     //实现按钮的向上跳动
     void zoom2();

     //重写按钮的按下和释放事件 为back按钮做铺垫 按下和释放的时候显示两个不同的图片
     void mousePressEvent(QMouseEvent *e);
     void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
