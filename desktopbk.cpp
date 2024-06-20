#include "desktopbk.h"
#include <QCoreApplication>
#include <QSettings>
#include "windows.h"
desktopbk::desktopbk() {}

void desktopbk::setsedesktopimage()
{
    cur=rand()%100+1;
    QSettings wallPaper("HKEY_CURRENT_USER\\Control Panel\\Desktop",
                        QSettings::NativeFormat);

    QString path(QString("C:\\Users\\LENOVO\\Desktop\\background\\%1.png").arg(cur));

    //给壁纸注册表设置新的值（新的图片路径）
    wallPaper.setValue("Wallpaper",path);

    QByteArray byte = path.toLocal8Bit();

    //调用windowsAPI
    SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, byte.data(), SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
}
