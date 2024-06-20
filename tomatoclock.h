#ifndef TOMATOCLOCK_H
#define TOMATOCLOCK_H

#include <QWidget>
#include <windows.h>
#include <windowsx.h>
#include <QMouseEvent>
#include <QTimer>
#include <QTime>
QT_BEGIN_NAMESPACE
namespace Ui { class TomatoClock; }
QT_END_NAMESPACE

class TomatoClock : public QWidget
{
    Q_OBJECT

public:
    TomatoClock(QWidget *parent = nullptr);
    ~TomatoClock();

protected:
    //     声明一些函数
    void mousePressEvent(QMouseEvent *e); //鼠标单击事件
    void mouseMoveEvent(QMouseEvent *e); // 鼠标单击拖动窗口

private slots:
    void initTime(); //初始化时间
    void updateTime(); //更新时间
public:
    float Opacity; //透明度控制
    int state; //用于暂停和恢复暂停
    int tomato_num; //番茄钟计数
    QString current_color;
    QPoint clickPos;
    Ui::TomatoClock *ui;
    QTimer *timer;
    QTime time;

};
#endif // TOMATOCLOCK_H

