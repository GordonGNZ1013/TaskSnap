#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 設定應用程式資訊
    QCoreApplication::setApplicationName("專案小幫手");
    QCoreApplication::setOrganizationName("專案小幫手");
    QCoreApplication::setApplicationVersion("1.0.0");

    MainWindow w;
    w.show();

    return a.exec();
}
