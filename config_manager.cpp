#include "config_manager.h"

config_manager::config_manager()
{
    __use_default_browser = true;
    login_url = "http://www.baidu.com";
    login_widget_height = 600;
    login_widget_width = 680;
    camera_widget_height = 520;
    camera_widget_width = 680;
    face_height = 480;
    face_width = 640;
    border_file_path = "border.png";
}
config_manager::~config_manager()
{
}
void config_manager::set_login_url(QString new_url)
{
    this->login_url = new_url;
}

QString config_manager::get_border_file_path() const
{
    return border_file_path;
}
void config_manager::set_browser_path(const QString &path)
{
    if (!path.isNull()) {
        this->browser_path = path;
        this->__use_default_browser = false;
    }
}

QString config_manager::get_browser_path()
{
    return this->browser_path;
}

void config_manager::use_default_browser(bool b)
{
    this->__use_default_browser = b;
}

bool config_manager::is_use_default_browser()
{
    return this->__use_default_browser;
}

QString config_manager::get_login_url() const
{
    return login_url;
}

int config_manager::get_login_widget_height() const
{
    return login_widget_height;
}
int config_manager::get_login_widget_width() const
{
    return login_widget_width;
}
int config_manager::get_camera_widget_height() const
{
    return camera_widget_height;
}
int config_manager::get_camera_widget_width() const
{
    return camera_widget_width;
}
int config_manager::get_face_height() const
{
    return face_height;
}
int config_manager::get_face_width() const
{
    return face_width;
}
