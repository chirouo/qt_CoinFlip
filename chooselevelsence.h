#ifndef CHOOSELEVELSENCE_H
#define CHOOSELEVELSENCE_H
#include <QPainter>
#include <QMainWindow>
#include "playscene.h"
class chooseLevelSence : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooseLevelSence(QWidget *parent = nullptr);

    //重写绘画事件 画背景图
    void paintEvent(QPaintEvent *);

    //创造一个指针维护要进入的关卡
    PlayScene *play=NULL;
signals:

    //自定义一个信号 点击back按钮后返回主界面 自定义信号只需要申明不需要实现
    void backToMainSence();

public slots:
};

#endif // CHOOSELEVELSENCE_H
