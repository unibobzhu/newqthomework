#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QMainWindow>
#include <QPixmap>
#include <qlabel.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class BackGround;
}
QT_END_NAMESPACE

class BackGround : public QMainWindow
{
    Q_OBJECT

public:
    explicit BackGround(QWidget *parent = nullptr);
    ~BackGround();
    void updateRoleAnimation();
    bool eventFilter(QObject* watched, QEvent* ev) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event);//弹出右键
    QMenu* mExitMenu;//右键菜单
    QAction* mExitAct;//菜单项
private:
    Ui::BackGround *ui;
    QLabel* roleLabel;
};

#endif // BACKGROUND_H
