#include "date.h"

Date::Date() {}

Date::Date(const std::initializer_list<Event>& Events,const QDate& qdate):ToDos(Events){
    //将所有活动初始化放入ToDos并进行排序
    //std::sort(ToDos.begin(),ToDos.end());


}
Date::Date(const QDate& qdate):QDate(qdate){}
bool operator==(const Date&D1,const Date&D2){
    return D1.year() == D2.year() and D1.month() == D2.month() and D1.day() == D2.day();
}

int Date::Date2int() const{
    int res = 372 * (year()-2000) + 31 * month() + day();//保证不重复
    return res;
}
