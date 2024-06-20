//这是一个存储日期数据的类
#ifndef DATE_H
#define DATE_H

#include <QDate>
#include <vector>
#include "event.h"
class Date : public QDate
{
public:
    Date();//空构造函数
    Date(const std::initializer_list<Event>&,const QDate& qdate = QDate(2020,1,1));//一个事件构造函数
    Date(const QDate& qdate);
    //需要一个哈希函数的辅助函数
    int Date2int() const;
    //判等号
    friend bool operator==(const Date&D1,const Date&D2);
public:
    std::vector<Event> ToDos;
};
namespace std{
template<>
struct hash<Date>: public __hash_base<size_t, Date>   //标准库中有这个继承，查看一下其实只是继承两个typedef而已，
                    //所以不写这个继承在这个例子中也是可以运行的
                    //但为了更好的使用这个hash，写上去会比较好
{
    size_t operator()(const Date& rhs) const noexcept    //这个const noexpect一定要写上去
    {
        return (std::hash<int>()(rhs.Date2int())); //当然，可以使用其他的方式来组合这个哈希值,
    }
};
}
#endif // DATE_H
