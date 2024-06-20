#include "qdatemodify.h"
#include "ui_qdatemodify.h"
#include "eventshow.h"
#include "dateform.h"
QDateModify::QDateModify(MainMzk *parent,const QDate& qdate)
    : QDialog(parent)
    , ui(new Ui::QDateModify)
    , mainmzk(parent)
{
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    hide();
    ui->setupUi(this);
    //将父类转换为MainMzk类以便获得date
    date = dynamic_cast<MainMzk*>(this->parent())->GetDateOf(qdate);
    for(int i=0;i<date.ToDos.size();i++)
    {
        //引入界面,初始化时包含了主界面，日期等信息
        EventShow* Interface = new EventShow(parent,date,i,ui->scrollAreaWidgetContents);
        Interface->move(0, i * Interface->height());
        Interface->show();
    }
}

QDateModify::~QDateModify()
{
    delete ui;
}

void QDateModify::on_pushButton_clicked()
{
    DateForm* SetNewDateEventInterface = new DateForm(mainmzk,date,-1,nullptr);
    SetNewDateEventInterface->show();
}


void QDateModify::on_SetNewEvent_clicked()
{
    qDebug()<<"YES!";
}
void QDateModify::on_NewEvent_clicked(){}

