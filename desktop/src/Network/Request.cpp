#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/asio/ssl.hpp>

#include <QFile>
#include <QDateTime>

#include "Exception.h"
#include "Request.h"
#include "NetConfig.h"

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace ssl = boost::asio::ssl;
namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;
using HttpRequest = boost::beast::http::request<boost::beast::http::string_body>;
using HttpResponse = boost::beast::http::response<boost::beast::http::string_body>;


Request::Request(MethodType method_type, ContentType conten_type, std::string api_path) {
    m_method_type = method_type;
    m_content_type = conten_type;
    m_api_path = api_path;
}

void setRequest(HttpRequest& request, MethodType method_type, ContentType content_type, std::string api_path, const QMap<QString, QString>& head, const QString& json_body, const QMap<QString, QString>& form_body) {
    switch (method_type) {
    case MethodType::post:
        request.method(http::verb::post);
        break;
    case MethodType::get:
        request.method(http::verb::get);
        break;
    case MethodType::put:
        request.method(http::verb::put);
        break;
    default:
        break;
    }

    std::string target = NetConfig::base_path + "/" + api_path;

    // 根据请求体类型，填入请求体数据
    switch (content_type) {
    case ContentType::none: {
        std::string query;
        for (auto it = form_body.begin(); it != form_body.end(); it++) {
            if (query.empty() == false)
                query += "&";
            query += it.key().toStdString() + "=" + it.value().toStdString();
        }
        if (form_body.size() > 0)
            target = target + "?" + query;
        break;
    }
    case ContentType::urlencode: {
        request.set(http::field::content_type, "application/x-www-form-urlencoded");
        std::string body;
        for (auto it = form_body.begin(); it != form_body.end(); it++) {
            if (form_body.empty() == false)
                body += "&";
            body += it.key().toStdString() + "=" + it.value().toStdString();
        }
        request.body() = body;
        break;
    }
    case ContentType::formdata: {
        auto timestamp = QDateTime::currentMSecsSinceEpoch();           // 使用毫秒级时间戳减少生成的分割符冲突
        std::string boundary = "----WebKitFormBoundary" + QString::number(timestamp).toStdString();
        request.set(http::field::content_type, "multipart/form-data; boundary=" + boundary);
        std::ostringstream body;
        for (auto it = form_body.begin(); it != form_body.end(); it++) {
            if (it.key().toStdString() == "file") {         // 处理文件
                QFile file(it.value());
                if (file.open(QIODevice::ReadOnly)) {
                    QByteArray data = file.readAll();
                    file.close();

                    body << "--" << boundary << "\r\n";
                    body << "Content-Disposition: form-data; name=\"" << it.key().toStdString() << "\"; filename=\"" << file.fileName().toStdString() << "\"\r\n";
                    body << "Content-Type: application/octet-stream\r\n\r\n"; // 根据需要设置内容类型
                    body << data.toStdString() << "\r\n";
                } else {
                    throw Exception(ExceptionType::FileReadAndWriteError);
                }
            } else {                                        // 普通请求参数
                body << "--" << boundary << "\r\n";
                body << "Content-Disposition: form-data; name=\"" << it.key().toStdString() << "\"\r\n\r\n";
                body << it.value().toStdString() << "\r\n";
            }
        }
        body << "--" << boundary << "--\r\n";
        request.body() = body.str();
        break;
    }
    case ContentType::json: {
        request.set(http::field::content_type, "application/json");
        request.body() = json_body.toStdString();
        break;
    }
    default:
        break;
    }

    request.target(target);
    request.set(http::field::host, NetConfig::server_address);
    request.version(NetConfig::protocol_version);

    // 添加请求头信息
    for (auto it = head.begin(); it != head.end(); it++) {
        request.set(it.key().toStdString(), it.value().toStdString());
    }

    request.prepare_payload();
}

Response Request::send() {
    try {
        if (NetConfig::request_protocol == "http") {
            return sendHttp();
        } else if (NetConfig::request_protocol == "https") {
            return sendHttps();
        }
    } catch (...) {
    }
}


Response Request::sendHttp() {
    asio::io_context io_context;

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(NetConfig::server_address, NetConfig::port);

    tcp::socket socket(io_context);
    asio::connect(socket, endpoints);

    HttpRequest request;
    setRequest(request, m_method_type, m_content_type, m_api_path, m_head, m_json_body, m_form_body);

    http::write(socket, request);

    beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    http::read(socket, buffer, res);

    std::string responst = beast::buffers_to_string(res.body().data());

    beast::error_code ec;
    socket.shutdown(tcp::socket::shutdown_both, ec);
    if (ec && ec != asio::error::not_connected) {
        throw Exception(ExceptionType::NetWorkError);
    }
}



Response Request::sendHttps()
{
    Response response;
    return response;
}
