#include "attach.h"
#include "ui_attach.h"
#include<QLabel>
#include<QMouseEvent>
#include<QPixmap>
attach::attach(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::attach)
{
    ui->setupUi(this);
    cur=rand()%20+1;
    setWindowFlags(Qt::FramelessWindowHint);//消除窗口边框
    setAttribute(Qt::WA_TranslucentBackground);//背景透明
    ui->centralwidget->setStyleSheet(QString("QWidget { background-image: url(C:/Users/LENOVO/Desktop/pic/%1.png); background-repeat: no-repeat; background-size: cover; }").arg(cur));
        //setStyleSheet(QString(" background-image: url(:/);""background-repeat: no-repeat;").arg(cur));

    ui->minButton->setIcon(QIcon("C:\\Users\\LENOVO\\Desktop\\func\\min.png"));
    ui->closeButton->setIcon(QIcon("C:\\Users\\LENOVO\\Desktop\\func\\close.png"));
    setStyleSheet("QPushButton{border:none;background color:black;width:32px;height:32px;}");
}

attach::~attach()
{
    delete ui;
}


void attach::mouseMoveEvent(QMouseEvent *ev)
{
    this->move(ev->globalPos()-lefttop);
}

void attach::mousePressEvent(QMouseEvent *ev)
{
    lefttop=ev->pos();
}

void attach::on_closeButton_clicked()
{
    this->close();
}

void attach::on_minButton_clicked()
{
    this->showMinimized();
}
