#include "mainmzk.h"
#include "ui_mainmzk.h"
#include "qdatemodify.h"
#include <QFile>
#include <QTextStream>
#include <QCloseEvent>
MainMzk::MainMzk(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainMzk)
{
    QFile historyData("C:\\Users\\LENOVO\\Desktop\\success\\data.txt");

    if(!historyData.open(QIODevice::ReadOnly | QIODevice::Text)) //打开文件用于读 判断是否正常打开
    {
        qDebug()<<"data.txt文件没有正常打开"<<historyData.errorString();
        return;
    }
    QTextStream in(&historyData);
    while(!in.atEnd()) //判断文件结尾
    {
        QString line = in.readLine();
        QTextStream linestream(&line);
        int year,month,day;
        //读入第一行的年月日
        linestream>>year>>month>>day;
        //获得日期
        Date date = Date(QDate(year,month,day));

        //获取event个数
        line = in.readLine();
        QTextStream eventCountStream(&line);
        int eventCnt;
        eventCountStream>>eventCnt;
        //逐个获取event
        for(int i=0;i<eventCnt;i++){
            int sT[2],eT[2];
            char color[3];
            //读取起始终止时间
            line = in.readLine();
            QTextStream TimeStream(&line);
            TimeStream>>sT[0]>>sT[1]>>eT[0]>>eT[1];
            //读取所需事务
            QString EventName = in.readLine();
            QString EventAddress = in.readLine();
            //读取事件颜色
            line = in.readLine();
            QTextStream ColorStream(&line);
            ColorStream>>color[0]>>color[1]>>color[2];
            //生成一个活动放入
            date.ToDos.push_back(
                Event(sT[0],sT[1],eT[0],eT[1],EventName,EventAddress,color[0],color[1],color[2]));
        }
        this->DateList.insert(date);


    }
    historyData.close(); //文件关闭
    ui->setupUi(this);
}

MainMzk::~MainMzk()
{

    delete ui;

}

void MainMzk::on_calendarWidget_activated(const QDate &date)
{
    QDateModify* OperatingPlace = new QDateModify(this,date);
    OperatingPlace->setGeometry(401,0,241,371);//设置日历操作页面宽度
    OperatingPlace->move(401,0);
    OperatingPlace->show();
}
Date MainMzk::GetDateOf(const QDate& qdate)const{
    auto pos = DateList.find(Date(qdate));
    if(pos!=DateList.end())
        return *pos;
    else
        return Date(qdate);
}
void MainMzk::closeEvent(QCloseEvent *event){
    QFile updateData("C:\\Users\\LENOVO\\Desktop\\success\\data.txt");

    // 尝试打开文件以写入模式
    if (!updateData.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法写入updateData.txt文件:" << updateData.errorString();
        return;
    }
    // 创建QTextStream对象关联文件
    QTextStream out(&updateData);
    for(const auto& date:DateList){


        out<<date.year()<<" "<<date.month()<<" "<<date.day()<<"\n";//输出年月日
        out<<date.ToDos.size()<<"\n";
        for(int i=0;i<date.ToDos.size();i++){
            const Event *event = &date.ToDos[i];
            out<<event->sTime[0]<<" "<<event->sTime[1]<<" ";
            out<<event->eTime[0]<<" "<<event->eTime[1]<<"\n";
            out<<event->_ToDoText<<"\n";
            out<<event->_Address<<"\n";
            out<<event->Color[0]<<event->Color[1]<<event->Color[2]<<"\n";
        }

    }
    QWidget::closeEvent(event);
}
void MainMzk::ModifyDate(const Date& date){
    auto address = DateList.find(date);//在DateList中寻找date的地址
    //如果找到就先删去
    if(address != DateList.end()){
        DateList.erase(address);
    }
    //然后将新信息插入
    DateList.insert(date);

}
