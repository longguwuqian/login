#include <QApplication>
#include <QDesktopWidget>
#include <QTranslator>
#include <QDesktopServices>
#include <QMessageBox>
#include <QUrl>
#include "login_widget.h"
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
    QTranslator *translator = new QTranslator(0);
    if (translator->load("i18n_zh_CN.qm", "./translations") == false) printf("aaaa");
    a.installTranslator(translator);

    login_widget w;
    w.setStyleSheet("QWidget {background-color: beige;}QLabel, QAbstractButton {font: bold;}QPushButton {background-color: palegoldenrod; border-width: 2px; border-color: darkkhaki; border-style: solid; border-radius: 5; padding: 3px; min-width: 9ex; min-height: 2.5ex; } QPushButton:hover {background-color: khaki; }QPushButton:pressed { padding-left: 5px; padding-top: 5px; background-color: #d0d67c;}");
    /*居中放置*/
    w.move((QApplication::desktop()->width() - w.width()) / 2,(QApplication::desktop()->height() - w.height()) / 2);

    w.show();
    return a.exec();
}
