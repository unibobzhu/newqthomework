#include "eventshow.h"
#include "ui_eventshow.h"
#include "QMouseEvent"
#include <QTimer>
#include "dateform.h"
EventShow::EventShow(MainMzk* mainmzk,const Date& date,int i,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EventShow)
    , mainmzk(mainmzk)
    , date(date)
    , eventIdx(i)
{
    //连接槽函数
    connect(this, &EventShow::customContextMenuRequested, this, &EventShow::on_EventShow_customContextMenuRequested);

    Event event = date.ToDos[i];
    ui->setupUi(this);
    ui->EventNameLabel->hide();
    ui->EndTime->setText(QStringLiteral("%1:%2%3").arg(event.eTime[0]).arg(event.eTime[1]<10?"0":"").arg(event.eTime[1]));
    ui->StartTime->setText(QStringLiteral("%1:%2%3").arg(event.sTime[0]).arg(event.sTime[1]<10?"0":"").arg(event.sTime[1]));
    ui->EventName->setText(event._ToDoText);
    ui->textBrowser->setText(event._Address);

}
//计时器代码，用于判断单双击
char cnt =0;
void delayTime(int k)
{
    QEventLoop eventloop;
    //QTimer::singleShot(50*k, &eventloop, SLOT(quit()));
    QTimer::singleShot(50*k, &eventloop, SLOT(quit()));
    eventloop.exec();
}

void EventShow::mouseDoubleClickEvent(QMouseEvent *Mevent)
{
}
EventShow::~EventShow()
{
    delete ui;
}

void EventShow::on_StartTime_windowIconTextChanged(const QString &iconText)
{
    ui->StartTime->setText(iconText);
}


void EventShow::on_StartTime_pressed()
{

}


void EventShow::on_StartTimeEdit_editingFinished()
{
    QString AccTime = ui->StartTimeEdit->text();//带小时分钟的时间，如11:00
    QStringList timeParts = AccTime.split(":");
    int hour,minute;//需要获取的小时与分钟
    if (timeParts.size() == 2) {
        bool ok;
        hour = timeParts[0].toInt(&ok);
        if(hour>23||hour<0) ok = false;
        if (!ok) {
            qDebug() << "Invalid hour format";
            ui->StartTimeEdit->hide();
            ui->StartTime->show();
            return;
        }

        minute = timeParts[1].toInt(&ok);
        if(minute>59||minute<0) ok = false;
        if (!ok) {
            qDebug() << "Invalid minute format";
            ui->StartTimeEdit->hide();
            ui->StartTime->show();
            return;
        }

        //qDebug() << "Hour:" << hour << "Minute:" << minute;
    } else {
        qDebug() << "Invalid time format";
        ui->StartTimeEdit->hide();
        ui->StartTime->show();
        return;
    }
    date.ToDos[eventIdx].sTime[0] = hour;
    date.ToDos[eventIdx].sTime[1] = minute;//将时间更新
    updateEvent();//更新数据
    ui->StartTime->setText(QStringLiteral("%1:%2%3").arg(hour).arg(minute<10?"0":"").arg(minute));
    ui->StartTimeEdit->hide();
    ui->StartTime->show();

}




void EventShow::on_StartTime_clicked()
{
    cnt++;
    delayTime(10);

    if(cnt == 1)
    {
        //qDebug()<<"单击";
        cnt = 0;
    }
    else if (cnt >= 2)
    {
        //qDebug()<<"双击";
        ui->StartTimeEdit->setText(ui->StartTime->text());  // 设置文本框的初始文本为按钮的文本
        ui->StartTimeEdit->move(ui->StartTime->pos());  // 将文本框移动到按钮位置
        ui->StartTimeEdit->resize(ui->StartTime->size());  // 调整文本框大小与按钮一致
        ui->StartTimeEdit->show();  // 显示文本框
        ui->StartTimeEdit->setFocus();  // 设置焦点到文本框
        ui->StartTime->hide();  // 隐藏按钮
        cnt = 0;
    }
}


void EventShow::on_StartTime_released()
{
}

void EventShow::updateEvent(){
    mainmzk->ModifyDate(date);
}

void EventShow::on_EventName_clicked()
{
    //实现删除效果
    ui->EventName->hide();
    ui->EventNameLabel->setText(QStringLiteral("<s>%1</s>").arg(ui->EventName->text()));
    ui->EventNameLabel->show();
    //ui->EventNameLabel->setText("<s>Event</s>");

}


void EventShow::on_EndTime_clicked()
{
    cnt++;
    delayTime(10);

    if(cnt == 1)
    {
        //qDebug()<<"单击";
        cnt = 0;
    }
    else if (cnt >= 2)
    {
        //qDebug()<<"双击";
        ui->EndTimeEdit->setText(ui->EndTime->text());  // 设置文本框的初始文本为按钮的文本
        ui->EndTimeEdit->move(ui->EndTime->pos());  // 将文本框移动到按钮位置
        ui->EndTimeEdit->resize(ui->EndTime->size());  // 调整文本框大小与按钮一致
        ui->EndTimeEdit->show();  // 显示文本框
        ui->EndTimeEdit->setFocus();  // 设置焦点到文本框
        ui->EndTime->hide();  // 隐藏按钮
        cnt = 0;
    }
}


void EventShow::on_EndTimeEdit_editingFinished()
{
    QString AccTime = ui->EndTimeEdit->text();//带小时分钟的时间，如11:00
    QStringList timeParts = AccTime.split(":");
    int hour,minute;//需要获取的小时与分钟
    if (timeParts.size() == 2) {
        bool ok;
        hour = timeParts[0].toInt(&ok);
        if(hour>23||hour<0) ok = false;
        if (!ok) {
            qDebug() << "Invalid hour format";
            ui->EndTimeEdit->hide();
            ui->EndTime->show();
            return;
        }

        minute = timeParts[1].toInt(&ok);
        if(minute>59||minute<0) ok = false;
        if (!ok) {
            qDebug() << "Invalid minute format";
            ui->EndTimeEdit->hide();
            ui->EndTime->show();
            return;
        }

        //qDebug() << "Hour:" << hour << "Minute:" << minute;
    } else {
        qDebug() << "Invalid time format";
        ui->EndTimeEdit->hide();
        ui->EndTime->show();
        return;
    }
    date.ToDos[eventIdx].eTime[0] = hour;
    date.ToDos[eventIdx].eTime[1] = minute;//将时间更新
    updateEvent();//更新数据
    ui->EndTime->setText(QStringLiteral("%1:%2%3").arg(hour).arg(minute<10?"0":"").arg(minute));
    ui->EndTimeEdit->hide();
    ui->EndTime->show();
}
void EventShow::contextMenuEvent(QContextMenuEvent *event){
    DateForm *DateChangeDialog = new DateForm(mainmzk,date,eventIdx,nullptr);
    DateChangeDialog->show();
}

void EventShow::on_EventShow_customContextMenuRequested(const QPoint &pos)
{
    DateForm *DateChangeDialog = new DateForm(mainmzk,date,eventIdx,nullptr);
    DateChangeDialog->show();
}
