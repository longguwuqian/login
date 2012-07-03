#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H
#include <QString>

class config_manager
{
public:
    static config_manager &get_instance(){ static config_manager cfg_mgr; return cfg_mgr;}
    ~config_manager();
    void set_browser_path(const QString &path);
    QString get_browser_path();
    void use_default_browser(bool b = true);
    bool is_use_default_browser();
    bool save_config();
    bool load_config();

private:
    config_manager();

    QString browser_path;
    bool __use_default_browser;
};

#endif // CONFIG_MANAGER_H
