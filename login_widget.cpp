#include "login_widget.h"
#include "ui_loginwidget.h"

login_widget::login_widget(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f)
{
    /*禁止改变大小*/
    this->setMaximumSize(800, 650);
    this->setMinimumSize(800, 650);

    hlayout = new QHBoxLayout;
    vlayout = new QVBoxLayout;
    cvwidget = new QOpenCVWidget(this, 50, 500, 600, 500, 600);
    right_widget = new QWidget(this);
    right_widget->setMaximumHeight(300);
    right_widget->setMinimumHeight(300);
    hlayout->addWidget(cvwidget);
    hlayout->addWidget(right_widget);
    btn_login = new QPushButton("LOGIN", right_widget);
    btn_config = new QPushButton("config", right_widget);
    btn_quit = new QPushButton("Quit", right_widget);
    le_username = new QLineEdit(right_widget);
    le_password = new QLineEdit(right_widget);
    lb_username = new QLabel("user name:", right_widget);
    lb_password = new QLabel("pass word:", right_widget);
    cb_use_password = new QCheckBox("use password", right_widget);
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
    vlayout->addWidget(btn_quit);
    vlayout->addWidget(btn_config);

    /////
    tmp_btn_save_img = new QPushButton("save img", right_widget);
    connect(tmp_btn_save_img, SIGNAL(clicked()), cvwidget, SLOT(saveImage()));
    vlayout->addWidget(tmp_btn_save_img);
    /////

    connect(cb_use_password, SIGNAL(clicked(bool)), le_password, SLOT(setEnabled(bool)));
    connect(cb_use_password, SIGNAL(clicked()), le_password, SLOT(clear()));
    connect(btn_config, SIGNAL(clicked()), this, SLOT(on_btn_config_clicked()));
    connect(btn_quit, SIGNAL(clicked()), this, SLOT(close()));
    right_widget->setLayout(vlayout);
    setLayout(hlayout);
}

login_widget::~login_widget()
{

}

void login_widget::on_btn_config_clicked()
{
    this->dlg_config = new config_dialog(this->right_widget);
    this->dlg_config->show();
}
