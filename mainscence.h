#ifndef MAINSCENCE_H
#define MAINSCENCE_H
#include "chooselevelsence.h"
#include <QMainWindow>

namespace Ui {
class MainScence;
}

class MainScence : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScence(QWidget *parent = 0);

    //重写painEvent事件
    void paintEvent(QPaintEvent*);

    //创键一个指针维护“选择关卡的场景”
    chooseLevelSence *chooseSence=NULL;
    ~MainScence();

private:
    Ui::MainScence *ui;
};

#endif // MAINSCENCE_H
