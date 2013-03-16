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

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "camera/camera_widget.h"
#include "config_dialog.h"

class login_widget : public QWidget
{
    Q_OBJECT
public:
    login_widget(QWidget *parent = 0, Qt::WindowFlags f = Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ~login_widget();

    camera_widget *wgt_camera;

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
    QWidget *wgt_down;
    config_dialog *dlg_config;

private slots:
    void call_config_dialog();
};

#endif // LOGIN_WIDGET_H
