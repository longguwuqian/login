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
    QLineEdit *le_username;
    QLineEdit *le_password;
    QLabel *lb_username;
    QLabel *lb_password;
    QCheckBox *cb_use_password;
    bool *use_password;
    QOpenCVWidget *cvwidget;
    QWidget *right_widget;
    config_dialog *dlg_config;

private slots:
    void on_btn_config_clicked();
};

#endif // LOGIN_WIDGET_H
