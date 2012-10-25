#include <QtGui>
#include "config_dialog.h"

config_dialog::config_dialog(QWidget *parent) :
    QDialog(parent)
{
    this->btn_save = new QPushButton(tr("save"), this);
    this->btn_cancel = new QPushButton(tr("cancel"), this);
    this->btn_choose_browser = new QPushButton(tr("choose browser..."));
    this->rbtn_use_default = new QRadioButton(tr("use default browser"));
    this->rbtn_use_manual = new QRadioButton(tr("manual browser config"));
    this->le_browser_path = new QLineEdit;
    this->gbx_browser = new QGroupBox(tr("browser settings"), this);

    QVBoxLayout *vlayout = new QVBoxLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;

    vlayout->addWidget(this->rbtn_use_default);
    vlayout->addWidget(this->rbtn_use_manual);
    hlayout->addWidget(this->le_browser_path);
    hlayout->addWidget(this->btn_choose_browser);
    vlayout->addLayout(hlayout);

    this->gbx_browser->setLayout(vlayout);

    vlayout = new QVBoxLayout;
    hlayout = new QHBoxLayout;
    vlayout->addWidget(this->gbx_browser);
    hlayout->addWidget(this->btn_save);
    hlayout->addWidget(this->btn_cancel);
    vlayout->addLayout(hlayout);
    this->setLayout(vlayout);

    this->setWindowTitle(tr("config"));

    this->rbtn_use_default->setChecked(true);
    this->le_browser_path->setEnabled(false);
    this->le_browser_path->setReadOnly(true);
    this->btn_choose_browser->setEnabled(false);
    this->__is_btn_cancel_clicked = false;

    config_manager::get_instance().use_default_browser(true);

    connect(this->btn_save, SIGNAL(clicked()), this, SLOT(close()));
    connect(this->btn_cancel, SIGNAL(clicked()), this, SLOT(on_btn_cancel_clicked()));
    connect(this->rbtn_use_manual, SIGNAL(toggled(bool)), this->le_browser_path, SLOT(setEnabled(bool)));
    connect(this->rbtn_use_manual, SIGNAL(toggled(bool)), this->btn_choose_browser, SLOT(setEnabled(bool)));
    connect(this->btn_choose_browser, SIGNAL(clicked()), this, SLOT(choose_browser()));
}
config_dialog::~config_dialog()
{
}

void config_dialog::on_btn_cancel_clicked()
{
    this->__is_btn_cancel_clicked = true;
    this->close();
}

void config_dialog::choose_browser()
{
    config_manager::get_instance().set_browser_path(QFileDialog::QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("*")));
    if (!config_manager::get_instance().get_browser_path().isNull()) {
        this->le_browser_path->setText(config_manager::get_instance().get_browser_path());
    }
}
void config_dialog::reject()
{
    this->close();
}
void config_dialog::closeEvent(QCloseEvent *e)
{
    if (this->rbtn_use_manual->isChecked() && this->le_browser_path->text().isEmpty() && !this->__is_btn_cancel_clicked) {
        QMessageBox::warning(this, tr("warning"), tr("you have to choose a browser"), QMessageBox::Ok);
        e->ignore();
    } else {
        e->accept();
    }
}
