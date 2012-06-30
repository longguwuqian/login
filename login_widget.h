#ifndef LOGIN_WIDGET_H
#define LOGIN_WIDGET_H

#include <QWidget>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    
private:
    Ui::LoginWidget *ui;
};

#endif // LOGIN_WIDGET_H
