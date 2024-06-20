#include "analogclock.h"
#include "ui_analogclock.h"
#include <QPainter>
#include <QTime>
#include <QTimerEvent>
#include <QDateTime>
#include <QWidget>
#define M_PI 3.14159265358

AnalogClock::AnalogClock(QWidget *parent) :
    QWidget(parent),//currentTimeZone(QTimeZone::systemTimeZone()) ,
    ui(new Ui::AnalogClock)
{
    ui->setupUi(this);

    //初始化
    m_user=new User;
    //设置窗体大小
    resize(m_user->m_x,m_user->m_y);

    //设置标题
    this->setWindowTitle("MyClock");

    //设置无边框&显示置顶
    setWindowFlags( Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);

    //设置透明度
    setAttribute(Qt::WA_TranslucentBackground);

    //刷新时间1000ms=1s
    m_timer=new QTimer(this);
    m_timer->start(1000);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(update()));

    //时针、分针、秒针颜色设置rgba
    hourColor=QColor (0, 0, 0,120);
    minuteColor=QColor(112, 127, 127, 121);
    secondColor=QColor(255, 0, 0,100);
}

AnalogClock::~AnalogClock()
{
    delete ui;
}



//由于系统窗口被设置为Qt::FramelessWindowHint会导致窗口不能被拖动。通过捕获鼠标移动事件从而实现窗口移动。
//鼠标按下
void AnalogClock::mousePressEvent(QMouseEvent *ev)
{
    mouse_flag=1;
    mouse_x=ev->x();
    mouse_y=ev->y();

    if(ev->buttons()==Qt::RightButton)
    {
        //每点击一次右键 m_clickClose+1
        m_clickClose++;
        //点击右键2次后关闭时钟
        if(m_clickClose==2)
            this->close();
    }
    if(ev->buttons()==Qt::LeftButton)
    {
        //每点击一次左键 m_clickColor+1
        m_clickColor++;
        //点击左键2次后时钟改变为深色or浅色
        if(m_clickColor==2){
            m_size=10;
            this->hourColor=QColor(253,224,224,150);
            this->minuteColor=QColor(153,210,250,200);
            this->secondColor=QColor(250,250,255,115);
        }
        if(m_clickColor==4){
            m_size=0;
            hourColor=QColor (0, 0, 0,120);
            minuteColor=QColor(112, 127, 127, 121);
            secondColor=QColor(255, 0, 0,100);
            m_clickColor=0;
        }
    }
}
//鼠标释放
void AnalogClock::mouseReleaseEvent(QMouseEvent *ev)
{
    mouse_flag=0;
}
//鼠标移动
void AnalogClock::mouseMoveEvent(QMouseEvent *ev)
{
    if(mouse_flag==1)
    {
        int x=this->x()+ev->x();
        int y=this->y()+ev->y();
        setGeometry(x-mouse_x,y-mouse_y,m_user->m_x,m_user->m_y);
    }
}

//绘图
void AnalogClock::paintEvent(QPaintEvent *event){
    //根据选择的大小改变时钟的大小
    resize(m_user->m_x,m_user->m_y);

    //这里p不能是指针，否则程序会崩溃
    QPainter p(this);
    //绘制时针、分针、秒针
    //四边形的点坐标数据，目前原点还在左上角。后面会移动到窗口中心。
    //QWindow坐标里Y轴是反的，负数表示朝上
    //点的顺序要么为顺时针要么为逆时针，否则绘出的图会不符合预期
    static const QPoint hourHand[5] = {
        QPoint(3, 5),
        QPoint(3, -50),
        QPoint(0,-52),
        QPoint(-3,-50),
        QPoint(-3, 5)
    };
    static const QPoint minuteHand[5] = {
        QPoint(2, 5),
        QPoint(2,-78),
        QPoint(0,-80),
        QPoint(-2,-78),
        QPoint(-2, 5)
    };
    static const QPoint secondHand[5] = {
        QPoint(1,15),
        QPoint(1,-85),
        QPoint(0,-90),
        QPoint(-1,-85),
        QPoint(-1,15)
    };
    //开启抗锯齿
    p.setRenderHint(QPainter::Antialiasing);
    //所有的点，都进行一次位移。也就是将整个图片的原点从左上角，移动到中心。
    p.translate(width() / 2, height() / 2);
    //根据窗口大小缩放。图形缩放都是对点的操作，背后都有矩阵参与计算
    int side = qMin(width(), height());
    p.scale(side / 200.0, side / 200.0);

    //获取当前时间
    QTime time = QTime::currentTime();
    //时针
    //不需要边框，只需要填充
    p.setPen(Qt::NoPen);
    p.setBrush(hourColor);
    p.save();
    //根据时间值计算旋转角度，1h30°
    p.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    //drawConvexPolygon绘制凸多边形
    p.drawConvexPolygon(hourHand, 5);
    p.restore();

    //小时的刻度线
    if(!m_user->in_style)
        //画笔的颜色，线宽
        p.setPen(QPen(hourColor,1.5));
    else
        p.setPen(QPen(hourColor,2.5));
    for (int i = 0; i < 12; ++i) {
        if(!m_user->in_style){
            p.drawLine(88, 0, 96, 0);
            p.rotate(30.0);
        }
        else{
            //几何风格下的时钟数字
            if(i==0||i==3||i==6||i==9){
                if(i==0)
                    p.drawText(-20, -64, 40, 40,
                               Qt::AlignHCenter | Qt::AlignTop,"12");
                if(i==3)
                    p.drawText(-20, -64, 40, 40,
                               Qt::AlignHCenter | Qt::AlignTop,"3");
                if(i==6)
                    p.drawText(-20, -64, 40, 40,
                               Qt::AlignHCenter | Qt::AlignTop,"9");
                if(i==9)
                    p.drawText(-20, -64, 40, 40,
                               Qt::AlignHCenter | Qt::AlignTop,"9");
            }
            else{
                p.drawLine(54, 0, 62, 0);
            }
            p.rotate(30.0);
        }

    }

    //分针
    p.setPen(Qt::NoPen);
    if(!m_user->in_style)
        p.setBrush(minuteColor);
    else
        p.setBrush(hourColor);
    p.save();
    //1min6°
    p.rotate(6.0 * (time.minute() + time.second() / 60.0));
    p.drawConvexPolygon(minuteHand, 5);
    p.restore();
    p.setPen(minuteColor);
    if(!m_user->in_style){
        //分钟的刻度线
        for (int j = 0; j < 60; ++j) {
            if ((j % 5) != 0)
                p.drawLine(91, 0, 96, 0);
            p.rotate(6.0);
        }

        //秒针
        p.setPen(Qt::NoPen);
        p.setBrush(secondColor);
        p.save();
        //1s6°
        p.rotate(6.0 *time.second());
        p.drawConvexPolygon(secondHand, 5);
        p.restore();
    }


    //圆心
    p.setPen(Qt::NoPen);
    p.setBrush(hourColor);
    //画圆
    p.drawEllipse(-6,-6,13,13);
    p.setBrush(QColor(255, 255, 255,100));
    p.drawEllipse(-2,-2,5,5);

    if(m_user->in_style){
        //Polygon
        //倒着的正五边形
        double P_x[5];
        double P_y[5];
        Polygon(5,80-4*m_size,P_x,P_y);
        p.setPen(QPen(hourColor,0.5));
        p.setBrush(QColor(255,255,255,0));
        QPolygon duo=QPolygon();
        for(int i=0;i<5;i++)
            duo<<QPoint(P_x[i],P_y[i]);
        p.drawPolygon(duo);

        //正五边形
        QPolygon duo1=QPolygon();
        for(int i=0;i<5;i++)
            duo1<<QPoint(-P_x[i],-P_y[i]);
        p.drawPolygon(duo1);

        //正十边形
        double P_x1[10];
        double P_y1[10];
        Polygon(10,80-4*m_size,P_x1,P_y1);
        QPolygon duo2=QPolygon();
        for(int i=0;i<10;i++)
            duo2<<QPoint(P_x1[i],P_y1[i]);
        p.drawPolygon(duo2);

        //点不在轴上的正十边形
        double P_x2[10];
        double P_y2[10];
        Polygon2(10,85-4*m_size,P_x2,P_y2);
        QPolygon duo3=QPolygon();
        for(int i=0;i<10;i++)
            duo3<<QPoint(P_x2[i],P_y2[i]);
        p.setPen(QPen(hourColor,2));
        p.drawPolygon(duo3);

        //九个点的连线
        p.rotate(6.0 *time.second());
        p.setPen(QPen(hourColor,0.5));
        double P_x3[5];
        double P_y3[5];
        Polygon(5,27-m_size,P_x3,P_y3);
        QPolygon duo4=QPolygon();
        for(int i=1;i<5;i++)
            duo4<<QPoint(P_x3[i],P_y3[i])<<QPoint(-P_x3[i],-P_y3[i]);
        p.drawPolygon(duo4);

        //正十边形缺一个点变成九边形
        p.setPen(hourColor);
        double P_x4[10];
        double P_y4[10];
        Polygon(10,27-m_size,P_x4,P_y4);
        QPolygon duo5=QPolygon();
        for(int i=1;i<10;i++)
            duo5<<QPoint(P_x4[i],P_y4[i]);
        p.drawPolygon(duo5);
    }

}

//Polygon
//起始点在y轴上
void AnalogClock::Polygon(int edge,int r,double P_x[],double P_y[]){
    double angle;
    angle=2*M_PI/edge;
    for(int i=0;i<edge;i++){
        angle=i*2*M_PI/edge;
        P_x[i]=sin(angle)*r;
        P_y[i]=cos(angle)*r;
    }
}
//起始点不在y轴上
void AnalogClock::Polygon2(int edge,int r,double P_x[],double P_y[]){
    double angle;
    double angle2;
    angle=2*M_PI/edge;
    angle2=M_PI/edge;
    for(int i=0;i<edge;i++){
        angle=i*2*M_PI/edge+angle2;
        P_x[i]=sin(angle)*r;
        P_y[i]=cos(angle)*r;
    }
}
