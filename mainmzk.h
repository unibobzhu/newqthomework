#ifndef MAINMZK_H
#define MAINMZK_H
#include <QDialog>
#include "unordered_set"
#include "date.h"
namespace Ui {
class MainMzk;
}

class MainMzk : public QDialog
{
    Q_OBJECT

public:
    explicit MainMzk(QWidget *parent = nullptr);
    ~MainMzk();
    void ModifyDate(const Date& date);//调整日期
    Date GetDateOf(const QDate& qdate)const;//获得QDate对应的某一Date日期
protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void on_calendarWidget_activated(const QDate &date);

private:
    Ui::MainMzk *ui;
    std::unordered_set<Date,std::hash<Date>> DateList;//所有的日期数据都在这里
};

#endif // MAINMZK_H
