#ifndef MYCLOCK_H
#define MYCLOCK_H

#include <QWidget>
#include <QObject>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <cmath>
#include "user.h"


//为了方便直接可以加入整个Qt GUI的头文件，事实上用不到那么多，可以像上面那样细化
//#include <QtGui>
//#include <QWidget>
//#include "user.h"


namespace Ui {
class AnalogClock;
}

class AnalogClock : public QWidget
{
    Q_OBJECT

public:
    explicit AnalogClock(QWidget *parent = nullptr);
    ~AnalogClock();

private:
    Ui::AnalogClock *ui;

    //绘图（时针、分针、秒针、刻度、几何图案、数字）
    void paintEvent(QPaintEvent *e);

    //为了切换深色浅色时改变几何图案的大小
    int m_size=0;
    //求出正多边形的坐标:函数名（边数，外接圆半径，存放x坐标的数组，存放y坐标的数组）
    void Polygon(int edge,int r,double[],double[]);
    void Polygon2(int edge,int r,double[],double[]);

    //鼠标
    //标记
    int mouse_flag=0;
    //鼠标点击的坐标
    int mouse_x;
    int mouse_y;
    //鼠标点击的次数
    int m_clickClose=0;
    int m_clickColor=0;
    //鼠标按下
    void mousePressEvent(QMouseEvent *ev);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent *ev);
    //鼠标移动
    void mouseMoveEvent(QMouseEvent *ev);

    //定时器
    QTimer *m_timer;

    //时针、分针、秒针的颜色（默认深色）
    QColor hourColor;
    QColor minuteColor;
    QColor secondColor;

    //使用说明
    User *m_user;
};
#endif // MYCLOCK_H
