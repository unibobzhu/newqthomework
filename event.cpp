#include "event.h"

Event::Event() {}

Event::Event(const int& sTimeHour,const int& sTimeMin,const int& eTimeHour,const int& eTimeMin,
             const QString& ToDoText,const QString& Address,char R,char G,char B):_ToDoText(ToDoText),_Address(Address)
{
    sTime[0] = sTimeHour;
    sTime[1] = sTimeMin;
    eTime[0] = eTimeHour;
    eTime[1] = eTimeMin;
    Color[0] = R;
    Color[1] = G;
    Color[2] = B;
}
