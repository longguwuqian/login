#ifndef QOPENCVWIDGET_H
#define QOPENCVWIDGET_H

#include <cv.h>
#include <highgui.h>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QImage>
#include <QFileDialog>

class QOpenCVWidget : public QWidget {
    Q_OBJECT

    private:
        QLabel *imagelabel;
        QVBoxLayout *layout;
        QImage image;
        CvCapture *camera;
        QWidget *parent;
    public:
        QOpenCVWidget(QWidget *parent = 0, int timer_interval = 50, int max_width = 300, int max_height = 300, int min_width = 300, int min_height = 300);
        ~QOpenCVWidget(void);
        void putImage(IplImage *);
    public slots:
        void saveImage();
    protected:
        void timerEvent(QTimerEvent*);
};

#endif // QOPENCVWIDGET_H
