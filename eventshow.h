#ifndef EVENTSHOW_H
#define EVENTSHOW_H

#include <QWidget>
#include "mainmzk.h"
namespace Ui {
class EventShow;
}

class EventShow : public QWidget
{
    Q_OBJECT

public:
    // i指的是date今天的第i个活动
    explicit EventShow(MainMzk* mainmzk,const Date& date,int i,QWidget *parent = nullptr);
    ~EventShow();

private slots:
    void on_StartTime_windowIconTextChanged(const QString &iconText);

    void on_StartTime_pressed();
    void on_StartTimeEdit_editingFinished();

    void on_StartTime_released();

    void on_StartTime_clicked();
    void updateEvent();//更新一下当前日期在mainmzk中的信息
    void on_EventName_clicked();

    void on_EndTime_clicked();

    void on_EndTimeEdit_editingFinished();

    void on_EventShow_customContextMenuRequested(const QPoint &pos);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
private:
    Ui::EventShow *ui;
    //指向MainMzk的指针，其中含有数据库
    MainMzk *mainmzk;
    //这一天event所在日期
    Date date;
    //活动的索引号
    int eventIdx;
};

#endif // EVENTSHOW_H
