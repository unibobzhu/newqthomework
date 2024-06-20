#ifndef DATEFORM_H
#define DATEFORM_H
#include "mainmzk.h"
#include <QDialog>

namespace Ui {
class DateForm;
}

class DateForm : public QDialog
{
    Q_OBJECT

public:
    explicit DateForm(MainMzk* mainmzk,const Date& date,int _EventIdx = -1,QWidget *parent = nullptr);
    ~DateForm();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DateForm *ui;
    MainMzk* mainmzk;//控制中心
    Date date;//当前日期
    int EventIdx;//活动编号 为-1时表示这个活动是新建的
};

#endif // DATEFORM_H
