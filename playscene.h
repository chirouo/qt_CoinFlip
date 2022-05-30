#ifndef PLAYSCENE_H
#define PLAYSCENE_H
//#include <QPaintEvent>
#include"mycoin.h"
#include <QMainWindow>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    //自己重写一个构造函数
    PlayScene(int levelNum);

    //成员属性记录选择的关卡
    int levelIndex=0;

    //重写QPaintEvent
    void paintEvent(QPaintEvent *event);

    //设置一个二维数组维护每个关卡的数据
    int gameArray[4][4];

    //创建一个数组维护我的游戏场景的二位数组
    MyCoin *coinBtnArray[4][4];

    //判断游戏是否胜利的bool值
    bool isWin;

signals:

    //自定义一个信号 点击back按钮后返回选择关卡场景 自定义信号只需要申明不需要实现
    void backToChooseLevelSence();

public slots:
};

#endif // PLAYSCENE_H
