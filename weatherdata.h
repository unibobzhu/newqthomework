#ifndef WEATHERDATA_H
#define WEATHERDATA_H
#include<QString>
#endif // WEATHERDATA_H
class Now//记录当前天气状态
{
public:
    QString city;
    QString weatherstate;
    QString code;
    QString temperature;
    Now()
    {
        city="北京";
        weatherstate="晴";
        code="0";
        temperature="30";
    }
};
