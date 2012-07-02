#ifndef LOGIN_WIDGET_H
#define LOGIN_WIDGET_H

class QWidget;
class QMessageBox;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QPushButton;
class QLineEdit;
class QCheckBox;
class QDialog;

#include <cv.h>
#include <highgui.h>
#include "opencv_widget.h"
#include "config_dialog.h"
#include "register_widget.h"

class login_widget : public QWidget
{
    Q_OBJECT
    
public:
    login_widget(QWidget *parent = 0, Qt::WindowFlags f = Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ~login_widget();

private:

    /////
    QPushButton *tmp_btn_save_img;
    /////

    QHBoxLayout *hlayout;
    QVBoxLayout *vlayout;
    QPushButton *btn_login;
    QPushButton *btn_config;
    QPushButton *btn_quit;
    QPushButton *btn_register;
    QLineEdit *le_username;
    QLineEdit *le_password;
    QLabel *lb_username;
    QLabel *lb_password;
    QCheckBox *cb_use_password;
    opencv_widget *wgt_cv;
    QWidget *wgt_right;
    config_dialog *dlg_config;
    register_widget *wgt_register;

private slots:
    void call_config_dialog();
    void call_register_widget();
};

#endif // LOGIN_WIDGET_H
