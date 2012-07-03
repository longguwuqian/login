#include <QApplication>
#include <QDesktopWidget>
#include <QTranslator>
#include <QDesktopServices>
#include <QUrl>
#include "login_widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*设置语言*/
    QTranslator *translator = new QTranslator(0);
    if (translator->load("i18n_zh_CN.qm", "./translations") == false) printf("aaaa");
    a.installTranslator(translator);

//

    login_widget w;
    /*居中放置*/
    w.move((QApplication::desktop()->width() - w.width()) / 2,(QApplication::desktop()->height() - w.height()) / 2);

    w.show();
    return a.exec();
}
