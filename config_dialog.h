#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QDialog>
#include <QPushButton>

class config_dialog : public QDialog
{
    Q_OBJECT
public:
    explicit config_dialog(QWidget *parent = 0);

private:
    QPushButton *btn_save;
    QPushButton *btn_cancel;
    
signals:
    
public slots:
    
};

#endif // SETTINGS_DIALOG_H
