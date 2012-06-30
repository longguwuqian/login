#include <QApplication>
#include "login_widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWidget w;
    w.show();
    
    return a.exec();
}
