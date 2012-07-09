#ifndef FACE_DETECT_H
#define FACE_DETECT_H

#include "cv.h"

class face_detect
{
public:
    face_detect(const char *path);
    ~face_detect();
    CvSeq* detect(IplImage * image, bool do_pyramids = true);
    void draw_to_image(CvSeq *faces, IplImage *image, bool do_pyramids = true);

private:
    static int get_dist_int(const CvPoint *p1, const CvPoint *p2);
    static void get_center(const CvRect *window, CvPoint *center);
    static CvScalar hsv2rgb(float hue);

    const char *face_path;
    CvHaarClassifierCascade *cascade;
    CvMemStorage *storage;
};

#endif // FACE_DETECT_H
