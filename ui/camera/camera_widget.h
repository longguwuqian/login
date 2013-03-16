#ifndef CAMERA_WIDGET_H
#define CAMERA_WIDGET_H

#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QImage>
#include <QFileDialog>
#include <QMutex>
#include <QWaitCondition>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "capture_thread.h"

class camera_widget : public QWidget {
    Q_OBJECT

    private:
        capture_thread *cpt_thread;
        int dev_num;

    public:        
        QLabel *lb_frame;

        camera_widget(QWidget *parent = 0, int device_number = 0, QString border_file_path = QString::null);
        ~camera_widget(void);

        void disconnect_camera();
        void connect_camera();
        bool is_camera_connected();
        void start_capture_thread();
        void stop_capture_thread();
        int get_input_source_width();
        int get_input_source_height();
        QImage &get_frame_qimage();
        IplImage *get_frame_iplimage();
    public slots:
        void update_frame(QImage *img_frame, QMutex *update_done_mutex, volatile bool *update_done);
};

#endif // QOPENCVWIDGET_H
