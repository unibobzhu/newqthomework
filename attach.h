#ifndef ATTACH_H
#define ATTACH_H

#include <QMainWindow>

namespace Ui {
class attach;
}

class attach : public QMainWindow
{
    Q_OBJECT

public:
    explicit attach(QWidget *parent = nullptr);
    ~attach();
    int cur;
    void mouseMoveEvent(QMouseEvent* ev);
    void mousePressEvent(QMouseEvent* ev);
private slots:
    void on_closeButton_clicked();

    void on_minButton_clicked();

private:
    Ui::attach *ui;
    QPoint lefttop;
};


#endif // ATTACH_H
