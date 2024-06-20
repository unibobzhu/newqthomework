#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QWidget>
#include <QTimer>
#include <QMouseEvent>
// 定义 TimeHMS 结构体
typedef struct TimeHMS {
    qint32 hour;
    qint32 minute;
    qint32 second;
} TimeHMS;

QT_BEGIN_NAMESPACE
namespace Ui { class Countdown; }
QT_END_NAMESPACE

class Countdown : public QWidget
{
    Q_OBJECT

public:
    explicit Countdown(QWidget *parent = nullptr);
    ~Countdown();
    TimeHMS hms; // TimeHMS 结构体实例
protected:
    //     声明一些函数
    void mousePressEvent(QMouseEvent *e); //鼠标单击事件
    void mouseMoveEvent(QMouseEvent *e); // 鼠标单击拖动窗口

private slots:
    void do_timer_timeout(); // 定时器超时处理函数
    void on_btnStart_clicked(); // 开始按钮点击处理函数
    void on_btnStop_clicked(); // 停止按钮点击处理函数

private:
    float Opacity; //透明度控制
    QString current_color;
    bool subtractOneSecond(); // 减去一秒的函数
    QPoint clickPos;

    Ui::Countdown *ui;
    QTimer *m_timer;


};

#endif // COUNTDOWN_H
