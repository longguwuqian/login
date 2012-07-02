#include <QString>
#include "browser_config.h"

browser_config::browser_config()
{
}

QString browser_config::find_default_browser()
{
#ifdef Q_OS_WIN32
    return find_default_browser_win32();
#elif defined Q_OS_LINUX
    return find_default_browser_X11();
#else
    return QString::null;
#endif
}

#ifdef Q_OS_WIN32
QString browser_config::find_default_browser_win32()
{
    return QString::null;
}
#endif

#ifdef Q_OS_UNIX
QString browser_config::find_default_browser_X11()
{
    return QString::null;
}
#endif
