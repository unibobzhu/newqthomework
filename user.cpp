#include "user.h"
#include <QTimeZone>
#include <QDateTime>
//#include <QDebug>
#include<QString>
#include<QObject>
User::User(QWidget *parent):
    QWidget (parent)
{
    //一开始的introduction界面大小
    resize(800,600);

    // //设置圆角窗口
    // QBitmap bmp(this->size());
    // bmp.fill();
    // QPainter p(&bmp);
    // p.setPen(Qt::NoPen);
    // p.setBrush(Qt::black);
    // p.drawRoundedRect(bmp.rect(),40,40);
    // setMask(bmp);

    //无边框
    setWindowFlags(Qt::FramelessWindowHint);

    Opacity = 0.8; // 透明度设置
    current_color = "background:#CD9B9B"; //当前背景色设置
    this->setStyleSheet(current_color);                 //设置背景颜色
    this->setWindowFlags(Qt::FramelessWindowHint);      //设置为无边框窗口
    this->setWindowOpacity(Opacity);                    //设置不透明度

    //名称
    setWindowTitle("Introduction of MyClock");
    show();
    //标题设置
    in_title.setParent(this);
    in_title.setText("Introduction of MyClock");
    in_title.setFont(QFont("Comic Sans MS",17,69));
    in_title.move(250,0);
    in_title.show();
    //文本设置
    in_text.setParent(this);
    in_text.setText(Text(text));
    in_text.setFont(QFont("黑体",12,60));
    in_text.move(10,40);
    in_text.show();
    //🆗按钮
    in_begin.setParent(this);
    in_begin.resize(60,30);
    in_begin.move(350,550);
    in_begin.setStyleSheet("QPushButton{background-color:rgba(240,240,240,50);}");
    in_begin.setText(QObject::tr("OK"));
    in_begin.setFont(QFont("Comic Sans MS",12,60));
    in_begin.show();
    //style按钮
    in_simple.setParent(this);
    in_simple.resize(90,30);
    in_simple.move(20,200);
    in_simple.setStyleSheet("QPushButton{background-color:rgba(240,240,240,50);}");
    in_simple.setText(QObject::tr("Simple"));
    in_simple.setFont(QFont("Comic Sans MS",12,60));
    in_simple.show();
    in_Polygon.setParent(this);
    in_Polygon.resize(90,30);
    in_Polygon.move(20,300);
    in_Polygon.setStyleSheet("QPushButton{background-color:rgba(240,240,240,50);}");
    in_Polygon.setText(QObject::tr("Polygon"));
    in_Polygon.setFont(QFont("Comic Sans MS",12,60));
    in_Polygon.show();
    //大小按钮
    in_big.setParent(this);
    in_medium.setParent(this);
    in_small.setParent(this);
    in_big.resize(30,30);
    in_medium.resize(30,30);
    in_small.resize(30,30);
    in_big.move(680,200);
    in_medium.move(680,300);
    in_small.move(680,400);
    in_big.setText(QObject::tr("big"));
    in_medium.setText(QObject::tr("middle"));
    in_small.setText(QObject::tr("small"));
    in_big.setFont(QFont("黑体",12,60));
    in_medium.setFont(QFont("黑体",12,60));
    in_small.setFont(QFont("黑体",12,60));
    in_big.setStyleSheet("QPushButton{background-color:rgba(240,240,240,50);}");
    in_medium.setStyleSheet("QPushButton{background-color:rgba(240,240,240,50);}");
    in_small.setStyleSheet("QPushButton{background-color:rgba(240,240,240,50);}");
    in_big.show();
    in_medium.show();
    in_small.show();


    //信号连接
    connect(&in_begin,&QPushButton::released,this,&User::begin);
    connect(&in_big,&QPushButton::released,this,&User::big);
    connect(&in_medium,&QPushButton::released,this,&User::medium);
    connect(&in_small,&QPushButton::released,this,&User::small);
    connect(&in_simple,&QPushButton::released,this,&User::style_s);
    connect(&in_Polygon,&QPushButton::released,this,&User::style_p);
}
User::~User(){}




//鼠标按下
void User::mousePressEvent(QMouseEvent *ev)
{
    mouse_flag=1;
    mouse_x=ev->x();
    mouse_y=ev->y();
}
//鼠标释放
void User::mouseReleaseEvent(QMouseEvent *ev)
{
    mouse_flag=0;
}
//鼠标移动
void User::mouseMoveEvent(QMouseEvent *ev)
{
    if(mouse_flag==1)
    {
        int x=this->x()+ev->x();
        int y=this->y()+ev->y();
        //后面两个数字的大小要与窗口大小一致，否则鼠标点击后窗口大小会变
        setGeometry(x-mouse_x,y-mouse_y,600,450);
    }
}


//槽函数
void User::begin(){
    this->hide();
}

void User::big(){
    m_x=450;
    m_y=450;
}

void User::medium(){
    m_x=300;
    m_y=300;
}

void User::small(){
    m_x=150;
    m_y=150;
}

void User::style_s(){
    in_style=false;
}

void User::style_p(){
    in_style=true;
}


// //背景渐变色
// void User::paintEvent(QPaintEvent *e){
//     QPainter painter(this);
//     //fillRect的值决定绘制的区域,QGradient颜色渐变
//     painter.fillRect(0, 0, width(), height(),QGradient::SeaLord);
// }

QString User::Text(QString text){
    QString introduce="         右键点击两次可关闭时钟,左键点击两次可更换时钟状态。注意，是点击时钟中心处哦！\n\n\n\n\n"
                        "   风格选择：                                                            大小选择：\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
                        "              点击🆗可关闭介绍界面：";
    text+= introduce;
    return text;
}
