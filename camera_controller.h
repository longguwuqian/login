#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H


// Qt header files
#include <QtGui>
// OpenCV header files
#include "highgui.h"
#include "capture_thread.h"

class camera_controller : public QObject
{
    Q_OBJECT

public:
    camera_controller(int device_num);
    ~camera_controller();
    capture_thread *cpt_thread;
    void disconnect_camera();
    void start_capture_thread();
    void stop_capture_thread();
    void delete_capture_thread();
    int get_input_source_width();
    int get_input_source_height();

};
#endif // CAMERA_CONTROLLER_H
