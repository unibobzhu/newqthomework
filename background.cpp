#include "background.h"
#include "ui_background.h"
#include "QTimer"
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include "MainMzk.h"
BackGround::BackGround(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BackGround)
    , roleLabel(new QLabel(this))
{   //去掉窗口边框，让背景透明
    setWindowFlags(Qt::WindowType::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //设置窗口大小
    this->resize(400,450);
    ui->setupUi(this);

    // 使用定时器更新动画
    QTimer* updateTimer = new QTimer(this);
    roleLabel->resize(400,450);
    updateTimer->callOnTimeout(this,&BackGround::updateRoleAnimation);
    updateTimer->start(500);


    //给窗口设置阴影
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
    effect->setColor(QColor(233,220,235));//浅色
    effect->setBlurRadius(5);
    this->setGraphicsEffect(effect);

    this->installEventFilter(this);


    mExitMenu=new QMenu(this);
    mExitAct=new QAction();
    mExitAct->setText("退出");
    mExitAct->setIcon(QIcon("C:\\Users\\LENOVO\\Desktop\\func\\close.png"));
    mExitMenu->addAction(mExitAct);     //右键退出
    connect(mExitAct,&QAction::triggered,this,[=]{
        qApp->exit(0);
    });
}

BackGround::~BackGround()
{
    delete ui;
}

void BackGround::updateRoleAnimation(){
    //展示图片
    //QString qss("background-repeat:no-repeat;");
    //roleLabel->setStyleSheet(qss+QString("background-image:url(:/new/Mizuki/source/target.png)"));
    QPixmap pixmap("C:\\Users\\LENOVO\\Desktop\\target.png");
    QPixmap scaledPixmap = pixmap.scaled(400, 450, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    roleLabel->setPixmap(scaledPixmap);

}

bool BackGround::eventFilter(QObject* watched, QEvent* ev){
    QMouseEvent* mouseev = static_cast<QMouseEvent*>(ev);
    static QPoint begpos;
    //判断鼠标左键按下
    if(ev->type() == QEvent::MouseButtonPress){
        begpos = mouseev->globalPos() - this->pos();
    }
    else if(ev->type()==QEvent::MouseMove&&mouseev->buttons()&Qt::MouseButton::LeftButton)
    {
        this->move(mouseev->globalPos() - begpos);
    }
    else if(ev->type()==QEvent::MouseMove&&mouseev->buttons()&Qt::MouseButton::RightButton)
    {

    }
    return false;

}
void BackGround::mouseDoubleClickEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        //qDebug() << "Left button double-clicked at position:" << event->pos();
        MainMzk* Mzk = new MainMzk(nullptr);
        //Mzk->resize(600,600);
        Mzk->show();
    } else if (event->button() == Qt::RightButton) {
        qDebug() << "Right button double-clicked at position:" << event->pos();
    }
}

void BackGround::contextMenuEvent(QContextMenuEvent *event)
{
    mExitMenu->exec(QCursor::pos());
}
