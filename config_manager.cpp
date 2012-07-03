#include "config_manager.h"
#include <QString>

config_manager::config_manager()
{
}

void config_manager::set_browser_path(const QString &path)
{
    this->browser_path = path;
}

QString config_manager::get_browser_path()
{
    return this->browser_path;
}

void config_manager::use_default_browser(bool b)
{
    this->__use_default_browser = b;
}

void config_manager::is_use_default_browser()
{
    return this->__use_default_browser;
}
