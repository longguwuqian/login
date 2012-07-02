#include "register_widget.h"
#include <QtGui>
#include <QGridLayout>

register_widget::register_widget(QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f)
{
    this->setMaximumSize(500, 400);
    this->setMinimumSize(500, 400);
    btn_regnow = new QPushButton("regnow", this);
    btn_cancel = new QPushButton("cancel", this);
    QGridLayout *glayout = new QGridLayout(this);
    glayout->addWidget(btn_cancel, 0, 0);
    glayout->addWidget(btn_regnow, 0, 1);
    this->setLayout(glayout);

    connect(btn_cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(btn_regnow, SIGNAL(clicked()), this, SLOT(close()));
}
