#include "QOpenCVWidget.h"

// Constructor
QOpenCVWidget::QOpenCVWidget(QWidget *parent, int timer_interval, int max_width, int max_height, int min_width, int min_height) : QWidget(parent) {
    this->parent = parent;
    camera = cvCreateCameraCapture(0);
    assert(camera);
    layout = new QVBoxLayout;
    imagelabel = new QLabel(this);
    QImage dummy(100,100,QImage::Format_RGB32);
    image = dummy;
    layout->addWidget(imagelabel);
    for (int x = 0; x < 100; x ++) {
        for (int y =0; y < 100; y++) {
            image.setPixel(x,y,qRgb(x, y, y));
        }
    }
    this->setMaximumSize(max_width, max_height);
    this->setMinimumSize(min_width, min_height);
    imagelabel->setPixmap(QPixmap::fromImage(image));
    startTimer(timer_interval);
    setLayout(layout);
}

QOpenCVWidget::~QOpenCVWidget(void) {

}

void QOpenCVWidget::putImage(IplImage *cvimage) {
    int cvIndex, cvLineStart;
    // switch between bit depths
    switch (cvimage->depth) {
        case IPL_DEPTH_8U:
            switch (cvimage->nChannels) {
                case 3:
                    if ( (cvimage->width != image.width()) || (cvimage->height != image.height()) ) {
                        QImage temp(cvimage->width, cvimage->height, QImage::Format_RGB32);
                        image = temp;
                    }
                    cvIndex = 0; cvLineStart = 0;
                    for (int y = 0; y < cvimage->height; y++) {
                        unsigned char red,green,blue;
                        cvIndex = cvLineStart;
                        for (int x = 0; x < cvimage->width; x++) {
                            // DO it
                            red = cvimage->imageData[cvIndex+2];
                            green = cvimage->imageData[cvIndex+1];
                            blue = cvimage->imageData[cvIndex+0];

                            image.setPixel(x,y,qRgb(red, green, blue));
                            cvIndex += 3;
                        }
                        cvLineStart += cvimage->widthStep;
                    }
                    break;
                default:
                    printf("This number of channels is not supported\n");
                    break;
            }
            break;
        default:
            printf("This type of IplImage is not implemented in QOpenCVWidget\n");
            break;
    }
    //imagelabel->setPixmap(QPixmap::fromImage(image));
    imagelabel->setPixmap(QPixmap::fromImage(image.scaled(imagelabel->width(), imagelabel->height())));
}
void QOpenCVWidget::timerEvent(QTimerEvent *)
{
    IplImage *img = cvQueryFrame(camera);
    this->putImage(img);
}
void QOpenCVWidget::saveImage()
{
    QString path = QFileDialog::getSaveFileName(this->parent, "save file dialog", ".", "*.png");
    if (path != NULL) image.save(path);
}
