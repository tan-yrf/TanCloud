#ifndef REQUEST_H
#define REQUEST_H

#include <string>

#include <QString>
#include <QMap>

#include "Response.h"

// 请求方法类型
enum MethodType {
    post_method,
    get_method,
    put_method
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
    void downloadFile(std::function<void(size_t, size_t)> progress, const bool& downloading, const QUrl& url, const QString& local_folder);
public:
    // 请求头
    QMap<QString, QString> m_head;

    // 请求体有两种，json和表单类型，根据 content_type 进行匹配
    QString m_json_body;
    QMap<QString, QString> m_form_body;

private:
    Response sendHttp();
    Response sendHttps();
    void downloadFileHttp(std::function<void(size_t, size_t)> progress, const bool& downloading, const std::string& file_path, const std::string& target, const std::string& host, const std::string& port, const std::string& path);
    void downloadFileHttps(std::function<void(size_t, size_t)> progress, const bool& downloading, const std::string& file_path, const std::string& target, const std::string& host, const std::string& port, const std::string& path);
    std::string m_api_path;
    MethodType m_method_type;
    ContentType m_content_type;
};

#endif // REQUEST_H
