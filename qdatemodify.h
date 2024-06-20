#ifndef QDATEMODIFY_H
#define QDATEMODIFY_H

#include <QDialog>
#include "mainmzk.h"
namespace Ui {
class QDateModify;
}

class QDateModify : public QDialog
{
    Q_OBJECT

public:
    explicit QDateModify(MainMzk *parent = nullptr,const QDate& qdate = QDate(2020,1,1));
    ~QDateModify();

private slots:
    void on_pushButton_clicked();

    void on_NewEvent_clicked();

    void on_SetNewEvent_clicked();

private:
    Ui::QDateModify *ui;
    MainMzk* mainmzk;
    Date date;
};

#endif // QDATEMODIFY_H
