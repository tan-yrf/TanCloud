#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void LoginSuccess();

private slots:
    void on_btn_login_clicked();

private:
    Ui::Login *ui;
    QString m_address;
    QString m_username;
    QString m_password;
};

#endif // LOGIN_H
