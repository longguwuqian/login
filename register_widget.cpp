#include "register_widget.h"
#include <QtGui>

register_widget::register_widget(opencv_widget *wgt_cv, QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setMaximumSize(500, 400);
    this->setMinimumSize(500, 400);

    QHBoxLayout *hlayout = new QHBoxLayout;
    QVBoxLayout *vlayout = new QVBoxLayout;

    btn_regnow = new QPushButton("regnow", this);
    btn_cancel = new QPushButton("cancel", this);

    this->wgt_cv_login = wgt_cv;
    this->wgt_cv_login->set_disable(true);
    /*保证login_widget中的wgt_cv已经关闭*/
    while (this->wgt_cv_login->is_enabled());

    this->wgt_cv = new opencv_widget(this, 50, 400, 300, 400, 300);
    vlayout->addWidget(this->wgt_cv);
    hlayout->addWidget(btn_regnow);
    hlayout->addWidget(btn_cancel);
    vlayout->addLayout(hlayout);
    this->setLayout(vlayout);
    connect(btn_cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(btn_regnow, SIGNAL(clicked()), this, SLOT(close()));
}
register_widget::~register_widget()
{
    delete this->wgt_cv;
    this->wgt_cv_login->set_enable(true);
}
