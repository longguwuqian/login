#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H
#include <QString>

class config_manager
{
public:
    static config_manager &get_instance(){ static config_manager cfg_mgr; return cfg_mgr;}
    ~config_manager();
    void set_s_code(QString &s_code);
    void set_login_status(bool status);
    void set_browser_path(const QString &path);
    QString get_browser_path();
    void use_default_browser(bool b = true);
    bool is_use_default_browser();
    bool save_config();
    bool load_config();
    int get_login_widget_height() const;
    int get_login_widget_width() const;
    int get_camera_widget_height() const;
    int get_camera_widget_width() const;
    int get_face_height() const;
    int get_face_width() const;
    QString get_border_file_path() const;
    void set_login_url(QString &url);
    void set_login_url(const char *url);
    QString get_login_url() const;

    bool is_loggedin;
    QString s_code;
private:
    config_manager();

    int login_widget_width;
    int login_widget_height;
    int camera_widget_width;
    int camera_widget_height;
    int face_width;
    int face_height;

    QString browser_path;
    QString border_file_path;
    QString login_url;
    bool __use_default_browser;
};

#endif // CONFIG_MANAGER_H
