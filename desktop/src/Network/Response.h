#ifndef RESPONSE_H
#define RESPONSE_H

#include <string>

#include <QString>
#include <QJsonObject>

class Response
{
public:
    Response(const std::string& str);

    void showMessage();

    int code;
    QString message;
    QJsonObject body;
};

#endif // RESPONSE_H
