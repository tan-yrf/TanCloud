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
    void downloadFile(std::function<void(size_t, size_t)> progress, const bool& downloading, const QString& target, const QString& save_folder_path);

    void uploadFile(std::function<void(size_t, size_t)> progress, const bool& uploading, const QString& target_folder, const QString& local_file_path);
public:
    // 请求头
    QMap<QString, QString> m_head;

    // 请求体有两种，json和表单类型，根据 content_type 进行匹配
    QString m_json_body;
    QMap<QString, QString> m_form_body;

private:
    Response sendHttp();
    Response sendHttps();
    void downloadFileHttp(std::function<void(size_t, size_t)> progress, const bool& downloading, const QString& target, const QString& save_folder_path);
    void downloadFileHttps(std::function<void(size_t, size_t)> progress, const bool& downloading, const QString& target, const QString& save_folder_path);

    void uploadFileHttp(std::function<void(size_t, size_t)> progress, const bool& uploading, const QString& target_folder, const QString& local_file_path);
    void uploadFileHttps(std::function<void(size_t, size_t)> progress, const bool& uploading, const QString& target_folder, const QString& local_file_path);

private:
    std::string generateBoundary();
private:
    std::string m_api_path;
    MethodType m_method_type;
    ContentType m_content_type;
};

#endif // REQUEST_H
