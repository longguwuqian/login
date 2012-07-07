#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H
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
    void connect_camera();
    bool is_camera_connected();
    void start_capture_thread();
    void stop_capture_thread();
    void delete_capture_thread();
    int get_input_source_width();
    int get_input_source_height();

private:
    int dev_num;
};
#endif // CAMERA_CONTROLLER_H
