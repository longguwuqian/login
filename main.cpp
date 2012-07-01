#include <QApplication>
#include <QDesktopWidget>
#include "login_widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login_widget w;
    /*居中显示*/
    w.move((QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2);

    w.show();
    return a.exec();
}
