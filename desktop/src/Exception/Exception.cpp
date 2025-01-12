#include "Exception.h"

Exception::Exception(ExceptionType type)
{
    m_type = type;
    switch (type) {
    case ExceptionType::SystemError:
        m_message = u8"系统异常";
    case ExceptionType::NetWorkError:
        m_message = u8"网络异常";
    case ExceptionType::ConfigError:
        m_message = u8"配置异常";
    default:
        m_message = u8"未知错误";
    }
}

const char *Exception::what() const noexcept
{
    return m_message.c_str();
}
