#ifndef BROWSER_CONFIG_H
#define BROWSER_CONFIG_H

class QString;

class browser_config
{
public:
    browser_config();
    ~browser_config();
    QString find_default_browser();

    QString get_browser_path() const;
    void set_browser_path(const QString &path);

private:
#ifdef Q_OS_WIN32
    QString find_default_browser_win32();
#endif

#ifdef Q_OS_UNIX
    QString find_default_browser_X11();
#endif

    QString browser_path;
};

#endif // BROWSER_CONFIG_H
