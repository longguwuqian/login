#include "config_manager.h"

config_manager::config_manager()
{
    __use_default_browser = true;
    login_url = "http://www.baidu.com";
}
config_manager::~config_manager()
{
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
