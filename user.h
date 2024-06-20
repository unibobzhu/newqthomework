#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QObject>
#include <QMouseEvent>
#include <QBitmap>
#include <QPainter>
#include <QGradient>

namespace Ui {
class User;
}

class User: public QWidget
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = nullptr);
    ~User();
    //窗口大小（默认）
    int m_x=450;
    int m_y=450;
    //简单or几何风格，默认简单风格
    bool in_style=false;

private:
    Ui::User *ui;
    //🆗按钮
    QPushButton in_begin;
    //大小切换按钮
    QPushButton in_big;
    QPushButton in_medium;
    QPushButton in_small;
    //风格切换按钮
    QPushButton in_simple;
    QPushButton in_Polygon;

    //标签（标题，文本内容）
    QLabel in_title;
    QLabel in_text;
    //定义文本内容
    QString text;
    QString Text(QString t);

    //绘图事件，定义渐变色背景
    //void paintEvent(QPaintEvent *e);

    QString current_color;//颜色
    float Opacity; //透明度控制

    //鼠标
    int mouse_flag=0;
    int mouse_x;
    int mouse_y;
    //鼠标按下
    void mousePressEvent(QMouseEvent *ev);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent *ev);
    //鼠标移动
    void mouseMoveEvent(QMouseEvent *ev);

    //void initializeTimeZones(); // 声明初始化时区函数


public slots:
    //信号和槽机制之槽函数
    void begin();
    void big();
    void medium();
    void small();
    void style_s();
    void style_p();

};

#endif // USER_H
