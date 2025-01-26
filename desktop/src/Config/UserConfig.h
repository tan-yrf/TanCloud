#ifndef USERCONFIG_H
#define USERCONFIG_H

#include <QString>

struct UserConfig {
    static QString id;
    static QString name;
    static qint64 space;
    static qint64 used;
    static QString token;
};

#endif // USERCONFIG_H
