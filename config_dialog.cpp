#include "config_dialog.h"
#include <QGridLayout>

config_dialog::config_dialog(QWidget *parent) :
    QDialog(parent)
{
    btn_save = new QPushButton("save", this);
    btn_cancel = new QPushButton("cancel", this);
    QGridLayout *glayout = new QGridLayout(this);
    glayout->addWidget(btn_cancel, 0, 0);
    glayout->addWidget(btn_save, 0, 1);
    this->setLayout(glayout);

    connect(btn_cancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(btn_save, SIGNAL(clicked()), this, SLOT(close()));
}
