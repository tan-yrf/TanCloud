#ifndef REQUEST_H
#define REQUEST_H

#include <string>

#include <QString>
#include <QMap>

#include "Response.h"

// 请求方法类型
enum MethodType {
    post,
    get,
    put
};

// 请求体编码格式
enum ContentType {
    none,
    urlencode,
    formdata,
    json
};

class Request {
public:
    Request(MethodType method_type, ContentType conten_type, std::string api_path);

    Response send();

private:
    Response sendHttp();
    Response sendHttps();

private:
    std::string m_api_path;
    MethodType m_method_type;
    ContentType m_content_type;

    // 请求头
    QMap<QString, QString> m_head;

    // 请求体有两种，json和表单类型，根据 content_type 进行匹配
    QString m_json_body;
    QMap<QString, QString> m_form_body;

};

#endif // REQUEST_H
