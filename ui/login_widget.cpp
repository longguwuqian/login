#include <QtGui>
#include "login_widget.h"
#include "config_manager.h"

login_widget::login_widget(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f)
{
    /*禁止改变大小*/
    this->setMaximumSize(config_manager::get_instance().get_login_widget_width(), config_manager::get_instance().get_login_widget_height());
    this->setMinimumSize(config_manager::get_instance().get_login_widget_width(), config_manager::get_instance().get_login_widget_height());

    hlayout = new QHBoxLayout;
    vlayout = new QVBoxLayout;
    vlayout_2 = new QVBoxLayout;
    wgt_camera = new camera_widget(this);
    wgt_down = new QWidget(this);
    btn_login = new QPushButton(tr("LOGIN"), wgt_down);
    btn_config = new QPushButton(tr("config"), wgt_down);
    btn_quit = new QPushButton(tr("Quit"), wgt_down);
    le_username = new QLineEdit(wgt_down);
    le_password = new QLineEdit(wgt_down);
    lb_username = new QLabel(tr("user name:"), wgt_down);
    lb_password = new QLabel(tr("pass word:"), wgt_down);
    lb_lostpassword = new QLabel(tr("<a href=\"http://user.qzone.qq.com/657166483\">lost password?</a>"), wgt_down);
    lb_lostpassword->setOpenExternalLinks(true);
    cb_use_password = new QCheckBox(tr("use password"), wgt_down);

    lb_username->adjustSize();
    lb_username->setWordWrap(true);
    lb_password->adjustSize();
    lb_password->setWordWrap(true);
    le_password->setEchoMode(QLineEdit::Password);
    le_password->setEnabled(false);
    cb_use_password->setChecked(false);

//    tmp_btn_save_img = new QPushButton("save img");

    hlayout->addWidget(lb_username);
    hlayout->addWidget(le_username);
    hlayout->addWidget(lb_password);
    hlayout->addWidget(le_password);
    hlayout->addWidget(cb_use_password);
    vlayout_2->addLayout(hlayout);
    hlayout = new QHBoxLayout;
    hlayout->addWidget(btn_login);
    hlayout->addWidget(btn_config);
    hlayout->addWidget(btn_quit);
    hlayout->addWidget(lb_lostpassword);
//    hlayout->addWidget(tmp_btn_save_img);
    vlayout_2->addLayout(hlayout);

    wgt_down->setLayout(vlayout_2);
    vlayout->addWidget(wgt_camera);
    vlayout->addWidget(wgt_down);

    this->setLayout(vlayout);
    this->setWindowTitle(tr("login"));

    connect(cb_use_password, SIGNAL(clicked(bool)), le_password, SLOT(setEnabled(bool)));
    connect(cb_use_password, SIGNAL(clicked()), le_password, SLOT(clear()));
    connect(btn_config, SIGNAL(clicked()), this, SLOT(call_config_dialog()));
    connect(btn_quit, SIGNAL(clicked()), this, SLOT(close()));
//    connect(tmp_btn_save_img, SIGNAL(clicked()), this->wgt_camera, SLOT(save_image_tmp()));
}

login_widget::~login_widget()
{
}

void login_widget::call_config_dialog()
{
    this->dlg_config = new config_dialog(this->wgt_down);
    this->dlg_config->exec();
}


