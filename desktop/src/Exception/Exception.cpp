#include <QMessageBox>
#include <QTimer>
#include <qabstractbutton.h>

#include "Exception.h"

Exception::Exception(ExceptionType type) {
    m_type = type;
    switch (type) {
    case ExceptionType::ServerConnectError:
        m_message = u8"服务器连接失败";
        break;
    case ExceptionType::SystemError:
        m_message = u8"系统异常";
        break;
    case ExceptionType::FileReadAndWriteError:
        m_message = u8"文件读写异常";
        break;
    case ExceptionType::NetWorkError:
        m_message = u8"网络异常";
        break;
    case ExceptionType::ConfigError:
        m_message = u8"配置异常";
        break;
    default:
        m_message = u8"网络异常";
    }
}

const char *Exception::what() const noexcept {
    return m_message.c_str();
}

void Exception::showMessage() {
    QMessageBox msg;
    msg.setWindowIcon(QIcon(":/ico.svg"));
    msg.setIcon(QMessageBox::Critical);
    msg.setWindowTitle("错误");
    msg.setText(QString::fromStdString(m_message));
    msg.addButton(QMessageBox::Ok);
    msg.button(QMessageBox::Ok)->hide();
    msg.exec();
}
