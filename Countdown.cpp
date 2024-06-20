#include "Countdown.h"
#include "ui_Countdown.h"
#include <QTime>
#include <QTimer>
#include <QMouseEvent>
#include <windows.h>
Countdown::Countdown(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Countdown)
{
    ui->setupUi(this);
    Opacity = 0.8; // 透明度设置
    this->setWindowOpacity(Opacity);                    //设置不透明度
    current_color = "background:#ADD8E6"; //当前背景色设置
    this->setStyleSheet(current_color);                 //设置背景颜色
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置为无边框窗口
    this->hms.hour = 0;
    this->hms.minute = 0;
    this->hms.second = 0;
    m_timer = new QTimer(this);
    m_timer->stop();    // 默认定时器关闭
    m_timer->setSingleShot(false);
    m_timer->setTimerType(Qt::PreciseTimer);
    // 间隔时间 1s
    m_timer->setInterval(1000);
    connect(m_timer, &QTimer::timeout, this, &Countdown::do_timer_timeout);
    // 置顶
    ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    //    // 不置顶
    //    ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);


}

Countdown::~Countdown()
{
    delete ui;
}
void Countdown::mousePressEvent(QMouseEvent *e)  //鼠标单击事件
{
    if(e->button()==Qt::LeftButton)
        clickPos=e->pos();

}
void Countdown::mouseMoveEvent(QMouseEvent *e)  //鼠标移动事件
{
    if(e->buttons()&Qt::LeftButton)
        move(e->pos()+pos()-clickPos); //父窗口的左上角+当前鼠标指针移动-初始单击时候鼠标指针的方向
}

// 减一秒
bool Countdown::subtractOneSecond()
{
    // 若全部等于0，则返回false
    if(hms.second <= 0 && hms.minute == 0 && hms.hour == 0){
        return false;
    }
    // 秒钟减1
    hms.second--;
    if(hms.second < 0){
        hms.minute--;
        hms.second = 59;
        if(hms.minute < 0){
            hms.hour--;
            hms.minute = 59;
        }
    }
    return true;
}

void Countdown::do_timer_timeout()
{
    bool retBool = this->subtractOneSecond();
    if(!retBool){
        // 停止timer
        m_timer->stop();
        return;
    }
    ui->lcdHour->display(hms.hour);
    ui->lcdMinute->display(hms.minute);
    ui->lcdSecond->display(hms.second);

}

// 开始
void Countdown::on_btnStart_clicked()
{
    m_timer->start();
    QTime tm = ui->timeEdit->time();
    this->hms.hour = tm.hour();
    this->hms.minute = tm.minute();
    this->hms.second = tm.second();
    qDebug("Hour=%d", tm.hour());
    qDebug("Minute=%d", tm.minute());
    qDebug("Second=%d", tm.second());
}
// 停止
void Countdown::on_btnStop_clicked()
{
    m_timer->stop();
}
