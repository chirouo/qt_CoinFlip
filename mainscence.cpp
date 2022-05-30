#include "mainscence.h"
#include "ui_mainscence.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
//添加多媒体模块
#include <QSound>



MainScence::MainScence(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScence)
{
    ui->setupUi(this);
    //配置主场景

    //设置固定大小
    setFixedSize(320,588);

    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币主场景");

    //退出按钮的实现
    connect(ui->actionQuit,&QAction::triggered,this,[=](){
        this->close();
    });


    //开始按钮 用指针保存他不然函数结束 图片就无了
    MyPushButton *startBtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    //实例化“选择关卡场景”
    chooseSence=new chooseLevelSence;

    //监听chooseSence场景中的back按钮的信号
    connect(chooseSence,&chooseLevelSence::backToMainSence,[=](){

        //设置主场景的位置与选择关卡场景一致
        this->setGeometry(chooseSence->geometry());
        //隐藏“选择关卡”
        chooseSence->hide();
        //显示主场景
        this->show();
    });

    //准备开始音效
    QSound *startSound=new QSound(":/res/TapButtonSound.wav",this);

    //监听按钮的状态
    connect(startBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"start按钮按下了";

        //播放开始音效
        startSound->play();
        startBtn->zoom1();
        startBtn->zoom2();
        //定时器设置一个延迟 保证用户进入关卡选择的时候能看到按钮的动画 静态函数
        QTimer::singleShot(500,[=](){

            //设置选择关卡场景的位置与主场景一致
            chooseSence->setGeometry(this->geometry());
            //隐藏mainScence
            this->hide();
            //显示“选择关卡”
            chooseSence->show();

        });
    });
}
void MainScence::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");

    //拉伸一下图片占满窗口
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画上背景上面的图标
    pix.load(":/res/Title.png");

    //缩放一下不然太大了
    //painter.drawPixmap(10,30,/*缩放的函数*/pix.scaled(pix.width()*0.5,pix.height()*0.5));
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}



//析构函数
MainScence::~MainScence()
{
    delete ui;
}
