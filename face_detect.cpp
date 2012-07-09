#include "face_detect.h"
#include "cmath"

face_detect::face_detect(const char *path)
{
    face_path = path;
    cascade = (CvHaarClassifierCascade*)cvLoadHaarClassifierCascade(face_path, cvSize( 20,20 ));
    storage = cvCreateMemStorage(0);
}

face_detect::~face_detect()
{
    cvReleaseMemStorage(&storage);
}

CvSeq* face_detect::detect(IplImage * image, bool do_pyramids)
{
    IplImage* small_image = image;
    CvSeq* faces;
    int scale = 1;
    /* if the flag is specified, down-scale the ÊäÈëÍ¼Ïñ to get a
       performance boost w/o loosing quality (perhaps) */
    if(do_pyramids) {
        small_image = cvCreateImage(cvSize(image->width / 2,image->height / 2), IPL_DEPTH_8U, 3);
        cvPyrDown( image, small_image, CV_GAUSSIAN_5x5 );
        scale = 2;
    }
    /* use the fastest variant */
    faces = cvHaarDetectObjects(small_image, this->cascade, this->storage, 1.2, 2, CV_HAAR_DO_CANNY_PRUNING,cvSize(0,0));
    if(small_image != image)
        cvReleaseImage( &small_image );
    return faces;
}

void face_detect::draw_to_image(CvSeq *faces, IplImage *image, bool do_pyramids)
{
    int scale = 1;
    if (do_pyramids) scale = 2;
    for(int i = 0; i < faces->total; i++) {
        CvRect face_rect = *(CvRect*)cvGetSeqElem(faces, i);
        cvRectangle(image, cvPoint(face_rect.x * scale,face_rect.y * scale),
                     cvPoint((face_rect.x + face_rect.width) * scale,
                             (face_rect.y + face_rect.height) * scale),
                     CV_RGB(255, 0, 0), 3);
    }
}

int face_detect::get_dist_int(const CvPoint *p1, const CvPoint *p2)
{
    return sqrt(double((p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y * p2->y)));
}

void face_detect::get_center(const CvRect *window, CvPoint *center)
{
    center->x = window->y + window->height / 2;
    center->y = window->x + window->width / 2;
}

CvScalar face_detect::hsv2rgb(float hue)
{
    static const int sector_data[][3]=
    {{0, 2, 1}, {1, 2, 0}, {1, 0, 2}, {2, 0, 1}, {2, 1, 0}, {0, 1, 2}};
    static int rgb[3], p, sector;
    hue *= 0.033333333333333333333333333333333f;
    sector = cvFloor(hue);
    p = cvRound(255 * (hue - sector));
    p ^= sector & 1 ? 255 : 0;
    rgb[sector_data[sector][0]] = 255;
    rgb[sector_data[sector][1]] = 0;
    rgb[sector_data[sector][2]] = p;
    return cvScalar(rgb[2], rgb[1], rgb[0], 0);
}
