#ifndef REGISTER_WIDGET_H
#define REGISTER_WIDGET_H

#include <QWidget>
#include <QPushButton>

class register_widget : public QWidget
{
    Q_OBJECT
public:
    explicit register_widget(QWidget *parent = 0, Qt::WindowFlags f = Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    
private:
    QPushButton *btn_regnow;
    QPushButton *btn_cancel;
signals:
    
public slots:
    
};

#endif // REGISTER_WIDGET_H
