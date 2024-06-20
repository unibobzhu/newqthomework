#include "dateform.h"
#include "ui_dateform.h"

DateForm::DateForm(MainMzk *mainmzk, const Date &date, int _EventIdx, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DateForm)
    , mainmzk(mainmzk)
    , date(date)
    , EventIdx(_EventIdx)
{
    ui->setupUi(this);
    if(EventIdx>=0)
    {
        Event event = date.ToDos[EventIdx];
        ui->StartTimeEdit->setText(QStringLiteral("%1:%2%3").arg(event.sTime[0]).arg(event.sTime[1]<10?"0":"").arg(event.sTime[1]));
        ui->EndTimeEdit->setText(QStringLiteral("%1:%2%3").arg(event.eTime[0]).arg(event.eTime[1]<10?"0":"").arg(event.eTime[1]));
        ui->EventEdit->setText(event._ToDoText);
        ui->AddressEdit->setText(event._Address);
    }
}

DateForm::~DateForm()
{
    delete ui;
}

void DateForm::on_buttonBox_accepted()
{
    //处理StartTimeEdit部分
    QString AccTime = ui->StartTimeEdit->text();//带小时分钟的时间，如11:00
    QStringList timeParts = AccTime.split(":");
    int sHour,sMinute;//需要获取的小时与分钟
    if (timeParts.size() == 2) {
        bool ok;
        sHour = timeParts[0].toInt(&ok);
        if(sHour>23||sHour<0) ok = false;
        if (!ok) {
            qDebug() << "Invalid hour format";
            return;
        }

        sMinute = timeParts[1].toInt(&ok);
        if(sMinute>59||sMinute<0) ok = false;
        if (!ok) {
            qDebug() << "Invalid minute format";
            return;
        }

        //qDebug() << "Hour:" << hour << "Minute:" << minute;
    } else {
        qDebug() << "Invalid time format";
        return;
    }

    AccTime = ui->EndTimeEdit->text();//带小时分钟的时间，如11:00
    timeParts = AccTime.split(":");
    int eHour,eMinute;
    if (timeParts.size() == 2) {
        bool ok;
        eHour = timeParts[0].toInt(&ok);
        if(eHour>23||eHour<0) ok = false;
        if (!ok) {
            qDebug() << "Invalid hour format";
            return;
        }

        eMinute = timeParts[1].toInt(&ok);
        if(eMinute>59||eMinute<0) ok = false;
        if (!ok) {
            qDebug() << "Invalid minute format";
            return;
        }

        //qDebug() << "Hour:" << hour << "Minute:" << minute;
    } else {
        qDebug() << "Invalid time format";
        return;
    }

    Event NewEvent = Event(sHour,sMinute,eHour,eMinute,ui->EventEdit->text(),ui->AddressEdit->text());
    if(EventIdx == -1){//说明新活动是最后加上去的，只需要放在向量后面
        date.ToDos.push_back(NewEvent);
    }
    else{//否则，就用NewEvent替换掉对应编号的Event
        date.ToDos[EventIdx] = NewEvent;
    }
    //相应的在mainmzk中提示日程变化
    mainmzk->ModifyDate(date);
    //最后更新整个qdatemodify
    mainmzk->on_calendarWidget_activated(QDate(date.year(),date.month(),date.day()));
}
