#ifndef QOPENCVWIDGET_H
#define QOPENCVWIDGET_H

#include <cv.h>
#include <highgui.h>
#include <QWidget>

class QPixmap;
class QLabel;
class QVBoxLayout;
class QImage;
class QFileDialog;

class opencv_widget : public QWidget {
    Q_OBJECT

    private:
        QLabel *imagelabel;
        QVBoxLayout *layout;
        QImage image;
        CvCapture *camera;
    public:
        opencv_widget(QWidget *parent = 0, int timer_interval = 50, int max_width = 300, int max_height = 300, int min_width = 300, int min_height = 300);
        ~opencv_widget(void);
        void put_image(IplImage *);
        void cvimage2qimage(const IplImage* cvimage, QImage &qimage);
    public slots:
        void save_image();
    protected:
        void timerEvent(QTimerEvent*);
};

#endif // QOPENCVWIDGET_H
