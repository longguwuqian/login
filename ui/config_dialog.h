#ifndef CONFIG_DIALOG_H
#define CONFIG_DIALOG_H
#include <QDialog>
#include "config_manager.h"

class QWidget;
class QPushButton;
class QRadioButton;
class QLineEdit;
class QGroupBox;
class QString;

class config_dialog : public QDialog
{
    Q_OBJECT
public:
    explicit config_dialog(QWidget *parent = 0);
    ~config_dialog();
    void closeEvent(QCloseEvent *e);
private:

    QPushButton *btn_save;
    QPushButton *btn_cancel;
    QPushButton *btn_choose_browser;
    QRadioButton *rbtn_use_default;
    QRadioButton *rbtn_use_manual;
    QLineEdit *le_browser_path;
    QGroupBox *gbx_browser;
    bool __is_btn_cancel_clicked;
    
public slots:
    void on_btn_cancel_clicked();
    void choose_browser();
    void reject();
protected:
    
};

#endif // SETTINGS_DIALOG_H
