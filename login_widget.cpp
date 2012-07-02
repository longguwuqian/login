#include <QtGui>
#include "login_widget.h"

login_widget::login_widget(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f)
{
    /*禁止改变大小*/
    this->setMaximumSize(800, 650);
    this->setMinimumSize(800, 650);

    hlayout = new QHBoxLayout;
    vlayout = new QVBoxLayout;
    wgt_cv = new opencv_widget(this, 50, 500, 600, 500, 600);
    wgt_right = new QWidget(this);
    wgt_right->setMaximumHeight(300);
    wgt_right->setMinimumHeight(300);
    hlayout->addWidget(wgt_cv);
    hlayout->addWidget(wgt_right);
    btn_login = new QPushButton("LOGIN", wgt_right);
    btn_config = new QPushButton("config", wgt_right);
    btn_quit = new QPushButton("Quit", wgt_right);
    btn_register = new QPushButton("Register", wgt_right);
    le_username = new QLineEdit(wgt_right);
    le_password = new QLineEdit(wgt_right);
    lb_username = new QLabel("user name:", wgt_right);
    lb_password = new QLabel("pass word:", wgt_right);
    cb_use_password = new QCheckBox("use password", wgt_right);
    lb_username->adjustSize();
    lb_username->setWordWrap(true);
    lb_password->adjustSize();
    lb_password->setWordWrap(true);
    le_password->setEchoMode(QLineEdit::Password);
    le_password->setEnabled(false);
    cb_use_password->setChecked(false);
    vlayout->addWidget(lb_username);
    vlayout->addWidget(le_username);
    vlayout->addWidget(lb_password);
    vlayout->addWidget(le_password);
    vlayout->addWidget(cb_use_password);
    vlayout->addWidget(btn_login);
    vlayout->addWidget(btn_register);
    vlayout->addWidget(btn_quit);
    vlayout->addWidget(btn_config);

    /////
    tmp_btn_save_img = new QPushButton("save img", wgt_right);
    vlayout->addWidget(tmp_btn_save_img);
    /////

    wgt_right->setLayout(vlayout);
    this->setLayout(hlayout);

    /////
    connect(tmp_btn_save_img, SIGNAL(clicked()), wgt_cv, SLOT(save_image()));
    /////
    connect(cb_use_password, SIGNAL(clicked(bool)), le_password, SLOT(setEnabled(bool)));
    connect(cb_use_password, SIGNAL(clicked()), le_password, SLOT(clear()));
    connect(btn_config, SIGNAL(clicked()), this, SLOT(call_config_dialog()));
    connect(btn_quit, SIGNAL(clicked()), this, SLOT(close()));
    connect(btn_register, SIGNAL(clicked()), this,SLOT(call_register_widget()));
}

login_widget::~login_widget()
{

}

void login_widget::call_config_dialog()
{
    this->dlg_config = new config_dialog(this->wgt_right);
    this->dlg_config->exec();
}
void login_widget::call_register_widget()
{
    this->wgt_register = new register_widget(this->wgt_cv);
    this->wgt_register->setWindowModality(Qt::ApplicationModal);//阻塞其他窗口
    this->wgt_register->show();
}
