#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
#include<QMouseEvent>
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include"weatherdata.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void contextMenuEvent(QContextMenuEvent *event);//弹出右键
    QMenu* mExitMenu;//右键菜单
    QAction* mExitAct;//菜单项
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    QPoint bias;
    void getWeatherInfo(QString citycode);
    void parsejson(QByteArray &byteArray);
    void updateUI();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* mNetAccessManager;
    void onReplied(QNetworkReply *reply);
    Now mnow;
};
#endif // MAINWINDOW_H
