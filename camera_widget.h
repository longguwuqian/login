#ifndef QOPENCVWIDGET_H
#define QOPENCVWIDGET_H

#include "cv.h"
#include "highgui.h"
#include <QWidget>

#include "camera_controller.h"

class QPixmap;
class QLabel;
class QVBoxLayout;
class QImage;
class QFileDialog;

class camera_widget : public QWidget {
    Q_OBJECT

    private:
        QLabel *lb_frame;
        QVBoxLayout *layout;

        camera_controller *camera_ctlr;
    public:
        camera_widget(QWidget *parent = 0, int max_width = 300, int max_height = 300, int min_width = 300, int min_height = 300);
        ~camera_widget(void);
        void set_enable(bool b = true);
        void set_disable(bool b = true);
        bool is_enabled();
        bool is_disabled();
    public slots:
        void save_image();
        void update_frame(const QImage &img_frame);
};

#endif // QOPENCVWIDGET_H
