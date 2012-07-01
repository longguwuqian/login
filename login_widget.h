#ifndef LOGIN_WIDGET_H
#define LOGIN_WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <cv.h>
#include <highgui.h>
#include "QOpenCVWidget.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT
    
public:
    LoginWidget(QWidget *parent = 0, Qt::WindowFlags f = Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ~LoginWidget();

private:
    Ui::LoginWidget *ui;

    /////
    QPushButton *tmp_btn_save_img;
    /////

    QPushButton *btn_login;
    QLineEdit *le_username;
    QLineEdit *le_password;
    QLabel *lb_username;
    QLabel *lb_password;
    QCheckBox *cb_use_password;
    bool *use_password;
    QOpenCVWidget *cvwidget;
    QWidget *right_widget;
};

#endif // LOGIN_WIDGET_H
