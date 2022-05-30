
#include "chooselevelsence.h"
#include <QMenuBar>
#include <QPixmap>
#include "mypushbutton.h"
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QSound>
chooseLevelSence::chooseLevelSence(QWidget *parent) : QMainWindow(parent)
{
    //选择关卡界面的音效
    QSound *chooseLevelSenceSound=new QSound(":/res/TapButtonSound.wav");
    //返回按钮的音效
    QSound *backSound=new QSound(":/res/BackButtonSound.wav");




    //选择关卡场景的大小和mainSence保持一致
    this->setFixedSize(320,588);

    //设置窗口标题
    this->setWindowTitle("选择关卡");

    //设置界面的图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //创建菜单栏
    QMenuBar *bar=menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu *startMenu=bar->addMenu("开始");

    //创建“退出”菜单项 对应的pushButton
    QAction *quitAction=startMenu->addAction("退出");

    //点击退出 实现退出游戏 信号槽
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });


    //右下角显示返回按钮 利用自己之前封装的按钮控件
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected");

    //养成设置父类的好习惯 防止内存泄漏
    backBtn->setParent(this);

    //把back按钮移动到界面右下角
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());


    //实现按下返回主界面的功能
    connect(backBtn,&MyPushButton::clicked,[=](){

        //播放返回按钮的音效
        backSound->play();

        //做一个延时的back  （发送信号慢一点，美观）
        QTimer::singleShot(500,this,[=](){
            emit this->backToMainSence();
        });

    });




    //创建选择关卡的按钮 一个for循环实现矩阵
    for(int i=0;i<20;i++)
    {   //创建按钮
        MyPushButton *menuButton=new MyPushButton(":/res/LevelIcon.png");
        menuButton->setParent(this);
        menuButton->move(25+i%4*70,130+i/4*70);

        //监听按钮的点击信号
        connect(menuButton,&MyPushButton::clicked,[=](){


            //播放选择关卡的音效
            chooseLevelSenceSound->play();

            QString str=QString("选择的是第%1关").arg(i+1);
            qDebug()<<str;

            //隐藏选择关卡场景
            this->hide();

            //显示进入的关卡的场景
            play= new PlayScene(i+1);//实例化场景
            //设置游戏场景的位置与选择关卡场景一致
            play->setGeometry(this->geometry());
            play->show();

            //监听PlayScene中back按钮的信号
            connect(play,&PlayScene::backToChooseLevelSence,[=](){
                //设置选择关卡场景的位置与游戏场景一致
                this->setGeometry(play->geometry());

                //显示ChooseLevelScene的场景
                this->show();

                //删除playScene场景的指针
                //因为我这里每个关卡不一样 不玩了可以删掉省内存
                delete play;
                play=NULL;
            });
        });
        //显示关卡上每个关卡对应的数字
        QLabel *label=new QLabel;
        //        label->setParent(menuButton);
        label->setParent(this);
        label->setFixedSize(menuButton->width(),menuButton->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);

        //设置label上的数字再按钮的矩形框居中的位置 可以试试没有这局代码的结果(简而言之设置对齐方式)
        label->setAlignment(Qt::AlignCenter);

        //设置label的鼠标穿透属性 不然label盖住了menuButton menuButton无法clicked
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }

}
//画选择关卡的背景图
void chooseLevelSence::paintEvent(QPaintEvent *)
{

    QPainter *painter=new QPainter(this);//可以用指针维护 其实对象也可以
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter->drawPixmap(0,0,this->width(),this->height(),pix);

    //再画一个好看的背景标题的照片
    pix.load(":/res/Title.png");
    painter->drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
