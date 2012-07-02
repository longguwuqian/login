#include <QtGui>
#include "opencv_widget.h"

// Constructor
opencv_widget::opencv_widget(QWidget *parent, int timer_interval, int max_width, int max_height, int min_width, int min_height)
    : QWidget(parent)
{
    camera = cvCreateCameraCapture(0);
    assert(camera);
    layout = new QVBoxLayout;
    imagelabel = new QLabel(this);
    QImage dummy(100, 100, QImage::Format_RGB32);
    image = dummy;
    layout->addWidget(imagelabel);
    for (int x = 0; x < 100; x ++) {
        for (int y =0; y < 100; y++) {
            image.setPixel(x, y, qRgb(x, y, y));
        }
    }
    this->setMaximumSize(max_width, max_height);
    this->setMinimumSize(min_width, min_height);
    imagelabel->setPixmap(QPixmap::fromImage(image));
    setLayout(layout);
    startTimer(timer_interval);
}

opencv_widget::~opencv_widget(void)
{
    if (camera != NULL) cvReleaseCapture(&camera);
}
void opencv_widget::cvimage2qimage(const IplImage *cvimage, QImage &qimage)
{
    static IplImage *_cvimage;
    if (!cvimage)
            return;
    qimage = QImage(QSize(cvimage->width, cvimage->height), QImage::Format_RGB888);
            // IplImage * to work with OpenCV functions
    _cvimage = cvCreateImageHeader(cvSize(cvimage->width, cvimage->height), 8, 3);
            // Share the buffer between QImage and IplImage *
    _cvimage->imageData = (char *)qimage.bits();
    cvCopy(cvimage, _cvimage, 0);
        // Convert it from BGR to RGB. QImage works with RGB and cvQueryFrame returns a BGR IplImage
    cvCvtColor(_cvimage, _cvimage, CV_BGR2RGB);
}

void opencv_widget::put_image(IplImage *cvimage)
{
   // QImage qimage;
    this->cvimage2qimage(cvimage, image);
    imagelabel->setPixmap(QPixmap::fromImage(image.scaled(imagelabel->width(), imagelabel->height())));
}
void opencv_widget::timerEvent(QTimerEvent *)
{
    IplImage *img = cvQueryFrame(camera);
    this->put_image(img);
}
void opencv_widget::save_image()
{
    QString path = QFileDialog::getSaveFileName((QWidget *)this->parent(), "save file dialog", ".", "*.png");
    if (path != NULL) image.save(path);
}
