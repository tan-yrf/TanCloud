#include <QApplication>

#include "Login/Login.h"
#include "MainWindow/MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Login login;
    login.show();

    MainWindow w;
    QObject::connect(&login, &Login::LoginSuccess, &w, &MainWindow::onLoginSuccess);

    return a.exec();
}

