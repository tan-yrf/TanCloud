#include "Login.h"
#include "ui_Login.h"

#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "Exception.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);

    // 加载配置文件，如果用户没有就生成一个配置文件夹和config.json
    QString home_path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString config_dir_path = home_path + "/.tancloud";
    QDir dir;
    if (dir.exists(config_dir_path) == false) {
        if (dir.mkpath(config_dir_path) == false) {
            throw Exception(ExceptionType::SystemError);
        }
    }

    QString config_file_path = config_dir_path + "/config.json";
    QFile file(config_file_path);
    if (file.exists()) {
        if (file.open(QIODevice::ReadOnly | QIODevice::Text) == false) {
            throw Exception(ExceptionType::SystemError);
        }
        QByteArray data = file.readAll();
        file.close();
        QJsonParseError parse_error;
        QJsonDocument doc = QJsonDocument::fromJson(data, &parse_error);
        if (parse_error.error != QJsonParseError::NoError || doc.isObject() == false) {
            throw Exception(ExceptionType::ConfigError);
        }
        QJsonObject obj = doc.object();
        m_address = obj.value("address").toString();
        m_username = obj.value("username").toString();
        m_password = obj.value("password").toString();
        ui->edit_address->setText(m_address);
        ui->edit_username->setText(m_username);
        ui->edit_password->setText(m_password);
    } else {
        if (file.open(QIODevice::WriteOnly) == false) {
            throw Exception(ExceptionType::SystemError);
        }
        QJsonObject obj;
        obj["address"] = "";
        obj["username"] = "";
        obj["password"] = "";
        QJsonDocument doc(obj);
        file.write(doc.toJson());
        file.close();
    }
}

Login::~Login()
{
    delete ui;
}

void Login::on_btn_login_clicked()
{
    m_address = ui->edit_address->text();
    m_username = ui->edit_username->text();
    m_password = ui->edit_password->text();

    QString home_path = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    QString config_path = home_path + "/.tancloud" + "/config.json";
    QFile file(config_path);
    if (file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text) == false) {
            throw Exception(ExceptionType::SystemError);
        }
        QJsonObject obj;
        obj["address"] = m_address;
        obj["username"] = m_username;
        obj["password"] = m_password;
        QJsonDocument doc(obj);
        file.write(doc.toJson());
        file.close();
    } else {
        throw Exception(ExceptionType::ConfigError);
    }


}

