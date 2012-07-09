#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QImage>
#include <QFileDialog>
#include <QMutex>

#include "cv.h"
#include "highgui.h"
#include "camera_controller.h"

class camera_widget : public QWidget {
    Q_OBJECT

    private:
        QLabel *lb_frame;
        QVBoxLayout *layout;

        camera_controller *camera_ctlr;
    public:
        camera_widget(QWidget *parent = 0, int max_width = 300, int max_height = 300, int min_width = 300, int min_height = 300);
        ~camera_widget(void);
    public slots:
        void save_image();
        void update_frame(QImage *img_frame, QMutex *update_done_mutex, QWaitCondition *update_done_condition, volatile bool *update_done);
};

#endif // QOPENCVWIDGET_H
