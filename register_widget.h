#ifndef REGISTER_WIDGET_H
#define REGISTER_WIDGET_H

#include <QWidget>
#include "camera_widget.h"

class QPushButton;

class register_widget : public QWidget
{
    Q_OBJECT
public:
    explicit register_widget(camera_widget *wgt_cv, QWidget *parent = 0, Qt::WindowFlags f = Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ~register_widget();
private:
    QPushButton *btn_regnow;
    QPushButton *btn_cancel;
    camera_widget *wgt_camera_login;
    camera_widget *wgt_camera;
signals:
};

#endif // REGISTER_WIDGET_H
