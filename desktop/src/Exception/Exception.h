#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

#include <QString>

enum class ExceptionType {
    ServerConnectError,
    SystemError,
    FileReadAndWriteError,
    NetWorkError,
    ConfigError,
    Unknow
};

class Exception : public std::exception {
public:
    explicit Exception(ExceptionType type);

    const char* what() const noexcept override;

    void showMessage();
private:
    ExceptionType m_type;
    std::string m_message;
};


#endif // EXCEPTION_H
