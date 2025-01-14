#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/asio/ssl.hpp>

#include "Request.h"
#include "NetConfig.h"


Request::Request(MethodType method_type, ContentType conten_type, std::string api_path)
{
    m_method_type = method_type;
    m_content_type = conten_type;
    m_api_path = api_path;
}

Response Request::Send()
{
    try {
        if (NetConfig::request_protocol == "http") {
            return SendHttp();
        } else if (NetConfig::request_protocol == "https") {
            return SendHttps();
        }
    } catch (...) {
    }
}

Response Request::SendHttp()
{
    Response response;
    return response;
}

Response Request::SendHttps()
{
    Response response;
    return response;
}
