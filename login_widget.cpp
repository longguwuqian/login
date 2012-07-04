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
    wgt_camera = new camera_widget(this, 500, 550, 500, 550);
    wgt_right = new QWidget(this);
    btn_login = new QPushButton(tr("LOGIN"), wgt_right);
    btn_config = new QPushButton(tr("config"), wgt_right);
    btn_quit = new QPushButton(tr("Quit"), wgt_right);
    btn_register = new QPushButton(tr("Register"), wgt_right);
    le_username = new QLineEdit(wgt_right);
    le_password = new QLineEdit(wgt_right);
    lb_username = new QLabel(tr("user name:"), wgt_right);
    lb_password = new QLabel(tr("pass word:"), wgt_right);
    cb_use_password = new QCheckBox(tr("use password"), wgt_right);

    wgt_right->setMaximumHeight(300);
    wgt_right->setMinimumHeight(300);

    lb_username->adjustSize();
    lb_username->setWordWrap(true);
    lb_password->adjustSize();
    lb_password->setWordWrap(true);
    le_password->setEchoMode(QLineEdit::Password);
    le_password->setEnabled(false);
    cb_use_password->setChecked(false);

    hlayout->addWidget(wgt_camera);
    hlayout->addWidget(wgt_right);
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
    this->setWindowTitle(tr("login"));

    /////
    connect(tmp_btn_save_img, SIGNAL(clicked()), wgt_camera, SLOT(save_image()));
    /////
    connect(cb_use_password, SIGNAL(clicked(bool)), le_password, SLOT(setEnabled(bool)));
    connect(cb_use_password, SIGNAL(clicked()), le_password, SLOT(clear()));
    connect(btn_config, SIGNAL(clicked()), this, SLOT(call_config_dialog()));
    connect(btn_quit, SIGNAL(clicked()), this, SLOT(close()));
    connect(btn_register, SIGNAL(clicked()), this,SLOT(call_register_widget()));


    this->btn_register->setDisabled(true);
    this->tmp_btn_save_img->setDisabled(true);
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
    this->wgt_reg = new register_widget(this->wgt_camera);
    this->wgt_reg->setWindowModality(Qt::ApplicationModal);//阻塞其他窗口
    this->wgt_reg->show();
}

bool login_widget::open_url(QString &url)
{
    bool status = true;
    if (url.isNull()) return false;
    if (config_manager::get_instance().is_use_default_browser()) {
        status = QDesktopServices::openUrl(QUrl(url));
    }
    return status;
}
