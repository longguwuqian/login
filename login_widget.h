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
class QString;
class QProcess;

#include <cv.h>
#include <highgui.h>
#include "camera_widget.h"
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
    QVBoxLayout *vlayout_2;
    QPushButton *btn_login;
    QPushButton *btn_config;
    QPushButton *btn_quit;
    QLineEdit *le_username;
    QLineEdit *le_password;
    QLabel *lb_username;
    QLabel *lb_password;
    QLabel *lb_lostpassword;
    QCheckBox *cb_use_password;
    camera_widget *wgt_camera;
    QWidget *wgt_down;
    config_dialog *dlg_config;
    QProcess *proc_browser;

private slots:
    void call_config_dialog();

    bool open_login_url();
};

#endif // LOGIN_WIDGET_H
