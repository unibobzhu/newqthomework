#ifndef EVENT_H
#define EVENT_H
#include <QString>
class Event
{
public:
    Event();
    //利用参数进行初始化一个活动
    Event(const int& sTimeHour,const int& sTimeMin,const int& eTimeHour,const int& eTimeMin,
          const QString& ToDoText="",const QString& Address="",char R=0,char G=0,char B=0);
public:
    int sTime[2];//起始时间，分别是小时和分钟
    int eTime[2];//终止时间
    QString _ToDoText;//需要做的事情
    QString _Address;//事情的位置
    char Color[3];//事件颜色
};

#endif // EVENT_H
