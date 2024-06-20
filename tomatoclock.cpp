#include "tomatoclock.h"
#include "./ui_tomatoclock.h"
#include "ui_tomatoclock.h"

TomatoClock::TomatoClock(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TomatoClock)
{
    ui->setupUi(this);
    Opacity = 0.8; // 透明度设置
    state = 1;   // 暂停，恢复暂停
    tomato_num = 0; //番茄钟计数
    current_color = "background:#CD9B9B"; //当前背景色设置
    this->setStyleSheet(current_color);                 //设置背景颜色
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置为无边框窗口
    //    this->setMinimumSize(100,50);                        //设置最小尺寸
    //    this->setMaximumSize(200,100);                      //设置最大尺寸
    this->setWindowOpacity(Opacity);                    //设置不透明度
    // 置顶
    ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    //    // 不置顶
    //    ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);

    timer = new QTimer;

    ui->Timer->setDigitCount(5);                    //设置显示位数为8位
    initTime();                                      //令LCD显示00:00:00
    timer->setInterval(1000);                        //设置定时器间隔为1000=1s
    //连接槽函数，将timer的timeout行为，连接到updateTime函数中
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    //当点击(clicked)pbStart时，调用函数pbStart_clicked
    //connect(ui->pbStart, SIGNAL(clicked()), this, SLOT(pbStart_clicked()));
    timer->start();  //启用定时器


}
TomatoClock::~TomatoClock()
{
    delete ui;
}



void TomatoClock::mousePressEvent(QMouseEvent *e)  //鼠标单击事件
{
    if(e->button()==Qt::LeftButton)
        clickPos=e->pos();

    this->setWindowOpacity(Opacity);
    if (state == 1){
        //暂停
        state = 0;
        this->setStyleSheet("background:#B5B5B5");    //设置暂停背景颜色
        Opacity = 0.2;
        timer->stop();
        this->setWindowOpacity(Opacity);                    //设置不透明度
    }else{//恢复
        state = 1;
        timer->start();
        this->setStyleSheet( current_color);          //恢复背景颜色
        Opacity = 0.8;
    }
    this->setWindowOpacity(Opacity);                    //设置不透明度
}
void TomatoClock::mouseMoveEvent(QMouseEvent *e)  //鼠标移动事件
{
    if(e->buttons()&Qt::LeftButton)
        move(e->pos()+pos()-clickPos); //父窗口的左上角+当前鼠标指针移动-初始单击时候鼠标指针的方向
}

//void move(const QPoint &amp;);
//其中move的原点是父窗口的左上角，  如果没有父窗口，则桌面即为父窗口


void TomatoClock::initTime()
{
    time.setHMS(0,0,0); //时间复位 0
    ui->Timer->display(time.toString("mm:ss"));
}

void TomatoClock::updateTime()
{
    //每次更新时间，time增加1
    time = time.addSecs(1);
    ui->Timer->display(time.toString("mm:ss"));
    if (time.minute() == 5 and tomato_num==1){
        //休息完毕，进入番茄钟
        tomato_num = 0;
        initTime();
        current_color = "background:#CD9B9B";
        this->setStyleSheet(current_color);    //进入番茄色
    }else if(time.minute() == 25){
        //番茄钟完毕，进入休息时间
        tomato_num = 1;
        initTime();
        current_color = "background:#9BCD9B";
        this->setStyleSheet(current_color);    //进入休息色
    }
}

