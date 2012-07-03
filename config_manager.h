#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H
class QString;

class config_manager
{
public:
    config_manager();
    ~config_manager();
    void set_browser_path(const QString &path);
    QString get_browser_path();
    void use_default_browser(bool b = true);
    bool is_use_default_browser();
private:
    QString browser_path;
    bool __use_default_browser;
};

#endif // CONFIG_MANAGER_H
