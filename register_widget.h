#ifndef REGISTER_WIDGET_H
#define REGISTER_WIDGET_H

#include <QWidget>
#include "opencv_widget.h"

class QPushButton;

class register_widget : public QWidget
{
    Q_OBJECT
public:
    explicit register_widget(opencv_widget *wgt_cv, QWidget *parent = 0, Qt::WindowFlags f = Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ~register_widget();
private:
    QPushButton *btn_regnow;
    QPushButton *btn_cancel;
    opencv_widget *wgt_cv;
signals:
    
public slots:
    
};

#endif // REGISTER_WIDGET_H
