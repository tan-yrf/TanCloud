#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/asio/ssl.hpp>

#include <fstream>
#include <ctime>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <functional>

#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>

#include "Exception.h"
#include "Request.h"
#include "NetConfig.h"

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace ssl = boost::asio::ssl;
namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;
using AsioRequest = boost::beast::http::request<boost::beast::http::string_body>;
using AsioResponse = boost::beast::http::response<boost::beast::http::string_body>;


Request::Request(MethodType method_type, ContentType conten_type, std::string api_path) {
    m_method_type = method_type;
    m_content_type = conten_type;
    m_api_path = api_path;
}

void setRequest(AsioRequest& request, MethodType method_type, ContentType content_type, std::string api_path, const QMap<QString, QString>& head, const QString& json_body, const QMap<QString, QString>& form_body) {
    switch (method_type) {
    case MethodType::post_method:
        request.method(http::verb::post);
        break;
    case MethodType::get_method:
        request.method(http::verb::get);
        break;
    case MethodType::put_method:
        request.method(http::verb::put);
        break;
    default:
        break;
    }

    std::string target = NetConfig::base_path + api_path;

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
        if (form_body.empty() == false && json_body.isEmpty()) {            // 处理键值对形式的json
            QJsonObject obj;
            for (auto it = form_body.begin(); it != form_body.end(); it++) {
                obj.insert(it.key(), it.value());
            }
            QJsonDocument doc(obj);
            request.body() = QString::fromUtf8(doc.toJson()).toStdString();
        } else {
            request.body() = json_body.toStdString();
        }
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
        } else {
            throw Exception(ExceptionType::ConfigError);
        }
    } catch (...) {
        throw Exception(ExceptionType::Unknow);
    }
}

void Request::downloadFile(std::function<void (size_t, size_t)> progress, const bool &downloading, const QUrl &url, const QString &local_folder) {
    try {
        if (QDir(local_folder).exists() == false){
            throw Exception(ExceptionType::FileReadAndWriteError);
        }

        std::string target = url.toString().toStdString();
        std::string host = url.host().toStdString();
        std::string port;
        std::string path = url.path().toStdString();

        if(url.port() != -1) {
            port = std::to_string(url.port());
        } else if(url.scheme() == "http") {             // 如果url中不包含端口信息,设置默认端口80
            port = "80";
        } else if(url.scheme() == "https") {            // 如果url中不包含端口信息,设置默认端口443
            port = "443";
        }

        QString file_name = QString::fromStdString(path).section('/', -1); // 或者使用 section('\\', -1) 处理 Windows 路径
        file_name = QUrl::fromPercentEncoding(file_name.toUtf8());
        QString full_path = QDir(local_folder).filePath(file_name);
        // qDebug() <<"\n filename:" << file_name << "\n";
        // qDebug() <<"\n fullepath:" << full_path << "\n";
        std::string utf8_path = full_path.toLocal8Bit().constData();
        qDebug() << u8"下载: 文件名" << file_name;
        qDebug() << u8"下载: 路径" << QString::fromStdString(utf8_path);

        if(url.scheme() == "http") {
            qDebug() << u8"http下载";
            downloadFileHttp(progress, downloading, utf8_path, target, host, port, path);
        } else if(url.scheme() == "https") {
            qDebug() << u8"https下载";
            downloadFileHttps(progress, downloading, utf8_path, target, host, port, path);
        }
    } catch (const boost::system::system_error& e) {
        throw Exception(ExceptionType::NetWorkError);
    } catch (const std::exception& e) {
        throw Exception(ExceptionType::SystemError);
    } catch(Exception& e){
        throw e;
    }
}


Response Request::sendHttp() {
    asio::io_context io_context;

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(NetConfig::server_address, NetConfig::port);

    tcp::socket socket(io_context);
    try {
        asio::connect(socket, endpoints);
    } catch(const boost::system::system_error& e) {
        qDebug() << u8"连接失败";
        throw Exception(ExceptionType::ServerConnectError);
    }

    AsioRequest request;
    setRequest(request, m_method_type, m_content_type, m_api_path, m_head, m_json_body, m_form_body);

    // qDebug() << "Request Headers:";
    // for (const auto& header : request.base()) {
    //     qDebug() << QString::fromStdString(header.name_string()) << ": " << QString::fromStdString(header.value());
    // }
    //qDebug() << u8"请求体： " << request.body();

    http::write(socket, request);

    beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    http::read(socket, buffer, res);

    std::string res_str = beast::buffers_to_string(res.body().data());

    beast::error_code ec;
    socket.shutdown(tcp::socket::shutdown_both, ec);
    if (ec && ec != asio::error::not_connected) {
        throw Exception(ExceptionType::NetWorkError);
    }

    //qDebug() << "响应状态码: " << res.result_int();
    //qDebug() << "响应内容: " << QString::fromStdString(beast::buffers_to_string(res.body().data()));
    if (res.result_int() != 200) {
        throw Exception(ExceptionType::NetWorkError);
    }

    Response response(res_str);
    return response;
}


Response Request::sendHttps() {
    asio::io_context io_context;

    // 只支持tls1.2和tls1.3版本
    ssl::context ssl_context(boost::asio::ssl::context::sslv23);
    ssl_context.set_options(boost::asio::ssl::context::default_workarounds |
                            boost::asio::ssl::context::no_sslv2 |
                            boost::asio::ssl::context::no_sslv3 |
                            boost::asio::ssl::context::no_tlsv1 |
                            boost::asio::ssl::context::no_tlsv1_1 |
                            boost::asio::ssl::context::tlsv12 |
                            boost::asio::ssl::context::tlsv13);

    ssl_context.set_default_verify_paths();
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(NetConfig::server_address, NetConfig::port);

    ssl::stream<tcp::socket> socket(io_context, ssl_context);
    try {
        asio::connect(socket.next_layer(), endpoints);
    } catch(const boost::system::system_error& e) {
        qDebug() << u8"连接失败";
        throw Exception(ExceptionType::ServerConnectError);
    }

    socket.handshake(ssl::stream_base::client);

    AsioRequest request;
    setRequest(request, m_method_type, m_content_type, m_api_path, m_head, m_json_body, m_form_body);

    http::write(socket, request);

    beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    http::read(socket, buffer, res);

    std::string res_str = beast::buffers_to_string(res.body().data());

    beast::error_code ec;
    socket.next_layer().shutdown(tcp::socket::shutdown_both, ec);  // 关闭读取和写入
    if (ec && ec != asio::error::not_connected) {
        throw Exception(ExceptionType::NetWorkError);
    }

    Response response(res_str);
    return response;
}

void Request::downloadFileHttp(std::function<void (size_t, size_t)> progress, const bool &downloading, const std::string &file_path, const std::string &target, const std::string &host, const std::string &port, const std::string &path) {
    asio::io_context io_context;

    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(host, port);

    tcp::socket socket(io_context);
    asio::connect(socket, endpoints);

    AsioRequest request{http::verb::get, path, 11};
    request.set(http::field::host, host);
    request.set(http::field::user_agent, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/129.0.0.0 Safari/537.36 Edg/129.0.0.0");
    request.target(target);
    request.set(http::field::connection, "close");                  // 请求完成后关闭连接

    http::write(socket, request);

    beast::flat_buffer buffer;
    http::response_parser<http::dynamic_body> parser;
    parser.get().set(http::field::connection, "close");
    parser.body_limit(std::numeric_limits<std::uint64_t>::max());   // 取消主体大小限制

    http::read_header(socket, buffer, parser);

    // 检查状态码
    if (parser.get().result() != http::status::ok) {
        throw Exception(ExceptionType::NetWorkError);
    }

    // 获取原始报头
    const auto& fields = parser.get().base();
    auto it = fields.find(http::field::content_length);
    std::uint64_t content_length = 0;
    if (it != fields.end()) {
        content_length = std::stoull(std::string(it->value()));
        std::cout << "Content Length: " << content_length << " bytes\n";
    } else {
        throw Exception(ExceptionType::NetWorkError);
    }

    // 以二进制模式打开文件以写入响应
    std::ofstream file(file_path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file for writing");
    }
    qDebug() << u8"文件打开成功";

    // 流式读取并写入数据
    size_t total_downloaded = 0;
    while (parser.is_done() == false) {
        http::read(socket, buffer, parser);
        const auto& body_data = parser.get().body().data();
        for (const auto& buffer : body_data) {
            file.write(static_cast<const char*>(buffer.data()), buffer.size());
            total_downloaded += buffer.size();

            if (progress){
                progress(content_length, total_downloaded);
            }
        }

        if (downloading == false) {
            std::cout << "\nDownload stopped.\n";
            break;
        }
    }
    file.close();

    beast::error_code ec;
    socket.shutdown(tcp::socket::shutdown_both, ec);
    if (ec && ec != asio::error::not_connected) {
        throw Exception(ExceptionType::NetWorkError);
    }
}

void Request::downloadFileHttps(std::function<void (size_t, size_t)> progress, const bool &downloading, const std::string &file_path, const std::string &target, const std::string &host, const std::string &port, const std::string &path) {

}
