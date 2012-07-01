#include "login_widget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f),
    ui(new Ui::LoginWidget)
{
    /*禁止改变大小*/
    this->setMaximumSize(800, 700);
    this->setMinimumSize(800, 700);

    QHBoxLayout *hlayout = new QHBoxLayout;
    cvwidget = new QOpenCVWidget(this, 50, 500, 600, 500, 600);
    right_widget = new QWidget(this);
    right_widget->setMaximumHeight(200);
    right_widget->setMinimumHeight(200);
    hlayout->addWidget(cvwidget);
    hlayout->addWidget(right_widget);
    QVBoxLayout *vlayout = new QVBoxLayout;
    btn_login = new QPushButton("LOGIN", this);
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

    /////
    tmp_btn_save_img = new QPushButton("save img", right_widget);
    connect(tmp_btn_save_img, SIGNAL(clicked()), cvwidget, SLOT(saveImage()));
    vlayout->addWidget(tmp_btn_save_img);
    /////

    connect(cb_use_password, SIGNAL(clicked(bool)), le_password, SLOT(setEnabled(bool)));
    connect(cb_use_password, SIGNAL(clicked()), le_password, SLOT(clear()));
    right_widget->setLayout(vlayout);
    setLayout(hlayout);
    ui->setupUi(this);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}
