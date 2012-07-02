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
#include <QDialog>
#include <QToolBox>
#include <cv.h>
#include <highgui.h>
#include "QOpenCVWidget.h"
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
    QOpenCVWidget *wgt_cv;
    QWidget *wgt_right;
    config_dialog *dlg_config;
    register_widget *wgt_register;

private slots:
    void call_config_dialog();
    void call_register_widget();
};

#endif // LOGIN_WIDGET_H
