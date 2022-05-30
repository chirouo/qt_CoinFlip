#include "playscene.h"
#include <QDebug>
#include<QMenuBar>
#include <QAction>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <QFont>
#include "mycoin.h"
#include "dataconfig.h"
#include "QPropertyAnimation"
#include <QSound>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
    //翻金币的音效
    QSound *flipSound=new QSound(":/res/ConFlipSound.wav");
    //返回按钮的音效
    QSound *backSound=new QSound(":/res/BackButtonSound.wav");
    //胜利按钮的音效
    QSound *winSound=new QSound(":/res/LevelWinSound.wav");



    QString str=QString("你进入了第%1关").arg(levelNum);
    qDebug()<<str;
    this->levelIndex=levelNum;

    //初始化游戏场景
    //设置游戏场景
    this->setFixedSize(320,588);

    //设置window的标题
    this->setWindowTitle("翻金币场景");

    //设置window的图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //创建菜单栏
    QMenuBar *bar=menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu *starMenu=new QMenu("开始");

    //创建“退出”菜单项
    QAction *quitAction=new QAction("退出");
    starMenu->addAction(quitAction);

    //点击退出 实现退出游戏的功能
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //创建返回按钮
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);

    //将按钮移动到右下角
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //监听按钮的信号 点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){

//        qDebug()<<"点击了PlayScene的back按钮";
        //播放返回按钮的音效
        backSound->play();

        QTimer::singleShot(500,this,[=](){

            //发送返回选择关卡场景的信号
            emit this->backToChooseLevelSence();
        });

    });

    //显示当前关卡数

    //设置字体 字体
    QFont font;
    font.setFamily("华文新魏");

    //设置字体大小
    font.setPointSize(20);

    //设置一个label显示设置的字体
    QLabel *label=new QLabel(this);
    QString str1=QString("Level: %1").arg(this->levelIndex);
    label->setFont(font);
    label->setText(str1);

    //用setGeometry =setFixSize+move；
    label->setGeometry(30,this->height()-50,130,50);



    //初始化每个关卡的二维数组
    dataConfig gameconfig;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            //去掉map的外壳（去掉键 只要其中的值即数组）
            this->gameArray[i][j]=gameconfig.mData[this->levelIndex][i][j];
        }
    }

    //显示游戏胜利的图片
    QLabel *winLabel =new QLabel;
    winLabel->setParent(this);
    QPixmap victorPix;
    victorPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,victorPix.width(),victorPix.height());
    winLabel->setPixmap(victorPix);
    //y的方向设置反方向 这样有砸下来的效果
    winLabel->move((this->width()-victorPix.width())*0.5,-victorPix.height());


    //显示翻金币中金币的背景图案
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            //绘制图片
            QPixmap pix=QPixmap(":/res/BoardNode(1).png");
            QLabel *label=new QLabel;
            label->setParent(this);
            label->setPixmap(pix);
            label->setGeometry(57+i*50,200+j*50,pix.width(),pix.height());

            //判断显示金币还是银币
            QString str;
            if(gameArray[i][j]==1)
            {
                str=":/res/Coin0001.png";
            }
            else

            {
                str=":/res/Coin0008.png";
            }

            //创建金币或者银币
            MyCoin *coin=new MyCoin(str);


            coin->setParent(this);

            //微调coin的位置 显示在label的正中间
            coin->move(59+i*50,204+j*50);

            //为金币的属性赋值
            coin->positionX=i;
            coin->positionY=j;
            //1为金币 0为银币
            coin->flag=this->gameArray[i][j];

            //把coin传入另一个金币的数组，以便后期维护；
            coinBtnArray[i][j]=coin;

            //点击金币进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                //播放翻金币的音效
                flipSound->play();

                coin->changeFlag();
                //更新一下我的二维数组 因为我翻转了金币或者银币后他对应的1或0就变了
                this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;

                //翻转周围的金币
                //延迟翻转周围的金币 玩家观感更好
                QTimer::singleShot(300,this,[=](){
                    if(coin->positionX+1<=3)//翻转周围右侧的金币的条件
                    {
                        coinBtnArray[coin->positionX+1][coin->positionY]->changeFlag();
                        //更新一下我的二维数组 因为我翻转了金币或者银币后他对应的1或0就变了
                        this->gameArray[coin->positionX+1][coin->positionY]= this->gameArray[coin->positionX+1][coin->positionY]==0?1:0;
                    }

                    if(coin->positionX-1>=0)//翻转周围左侧的金币的条件
                    {
                        coinBtnArray[coin->positionX-1][coin->positionY]->changeFlag();
                        //更新一下我的二维数组 因为我翻转了金币或者银币后他对应的1或0就变了
                        this->gameArray[coin->positionX-1][coin->positionY]= this->gameArray[coin->positionX-1][coin->positionY]==0?1:0;
                    }

                    if(coin->positionY+1<=3)//翻转周围下侧的金币的条件
                    {
                        coinBtnArray[coin->positionX][coin->positionY+1]->changeFlag();
                        //更新一下我的二维数组 因为我翻转了金币或者银币后他对应的1或0就变了
                        this->gameArray[coin->positionX][coin->positionY+1]= this->gameArray[coin->positionX][coin->positionY+1]==0?1:0;
                    }

                    if(coin->positionY-1>=0)//翻转周围上侧的金币的条件
                    {
                        coinBtnArray[coin->positionX][coin->positionY-1]->changeFlag();
                        //更新一下我的二维数组 因为我翻转了金币或者银币后他对应的1或0就变了
                        this->gameArray[coin->positionX][coin->positionY-1]= this->gameArray[coin->positionX][coin->positionY-1]==0?1:0;
                    }



                    //判断游戏是否胜利
                    this->isWin=true;//默认你是胜利的
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinBtnArray[i][j]->flag==false)
                            {
                                this->isWin=false;
                                break;
                            }
                        }
                    }

                    if(this->isWin==true)
                    {
                        //播放胜利的音效
                        winSound->play();
//                        qDebug()<<"游戏胜利";

                        //将每个coin的isWin变为true
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinBtnArray[i][j]->isWin_Coin=true;
                            }
                        }

                        //胜利后 将胜利的图片砸下来
                        QPropertyAnimation *winAnimation=new QPropertyAnimation(winLabel,"geometry");

                        //设置时间的间隔为1000ms
                        winAnimation->setDuration(1000);
                        //设置开始位置
                        winAnimation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        winAnimation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        winAnimation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        winAnimation->start();

                    }
                });
            });
        }
    }

}

//重写QPaintEvent
void PlayScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //加载背景图
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");

    //画背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载背景图上的小装饰
    pix.load(":/res/Title.png");

    //缩放背景图上的小装饰
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);

    //画背景图上的小装饰
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
