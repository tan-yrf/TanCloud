#include <QJsonDocument>
#include <QMessageBox>
#include <qabstractbutton.h>

#include "Response.h"

Response::Response(const std::string &str) {
    QString json_str = QString::fromStdString(str);
    QJsonDocument doc = QJsonDocument::fromJson(json_str.toUtf8());
    if (doc.isObject()) {
        QJsonObject obj = doc.object();
        if (obj.contains("code") && obj["code"].isDouble()) {
            code = obj["code"].toInt();
        } else {
            code = -1;
        }

        if (obj.contains("message") && obj["message"].isString()) {
            message = obj["message"].toString();
        } else {
            message = "Unknow";
        }

        if (obj.contains("body") && obj["body"].isObject()) {
            body = obj["body"].toObject();
        } else {
            body = QJsonObject();
        }
    } else {
        code = -1;
        message = "Invalid JSON response";
        body = QJsonObject();
    }
}

void Response::showMessage() {
    QMessageBox msg;
    msg.setWindowIcon(QIcon(":/ico.svg"));
    msg.setIcon(QMessageBox::Information);
    msg.setWindowTitle(" ");
    msg.setText(message);
    msg.addButton(QMessageBox::Ok);
    msg.button(QMessageBox::Ok)->hide();
    msg.exec();
}
