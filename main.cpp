#include <QApplication>
#include <QDesktopWidget>
#include <QTranslator>
#include <QDesktopServices>
#include <QMessageBox>
#include <QUrl>
#include "login_client.h"
#include "QtSingleApplication"

int main(int argc, char *argv[])
{
    /*只允许运行一个实例*/
    QtSingleApplication a(argc, argv);
    if (a.isRunning()) {
        QMessageBox::information(0, QObject::tr("login"), QObject::tr("An instance has already been running!"));
        return 0;
    }

    /*设置语言*/
    QTranslator *translator1 = new QTranslator(0);
    QTranslator *translator2 = new QTranslator(0);
    translator1->load("i18n_zh_CN.qm", "./translations");
    translator2->load("qt_zh_CN.qm", "./translations");
    a.installTranslator(translator1);
    a.installTranslator(translator2);

    login_client lc;
    lc.start();
    return a.exec();
}
