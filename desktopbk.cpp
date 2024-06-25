#include "desktopbk.h"
#include <QCoreApplication>
#include <QSettings>
#include <QImage>
#include <QScreen>
#include "windows.h"

desktopbk::desktopbk() {}

void desktopbk::setsedesktopimage()
{
    cur = rand() % 100 + 1;
    QString path(QString("C:\\Users\\LENOVO\\Desktop\\background\\%1.png").arg(cur));

    // 加载图片
    QImage image(path);
    if (image.isNull()) {
        // 处理加载失败的情况
        return;
    }

    // 获取屏幕尺寸
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    // 缩放图片以适应屏幕大小
    QImage scaledImage = image.scaled(screenWidth*1.5,1.5*screenHeight,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    // 保存缩放后的图片到临时文件
    QString tempPath = QString("C:\\Users\\LENOVO\\Desktop\\background\\temp_%1.png").arg(cur);
    scaledImage.save(tempPath);

    // 设置壁纸
    QSettings wallPaper("HKEY_CURRENT_USER\\Control Panel\\Desktop", QSettings::NativeFormat);
    wallPaper.setValue("Wallpaper", tempPath);

    QByteArray byte = tempPath.toLocal8Bit();

    // 调用Windows API
    SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, byte.data(), SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
}
