#include <QApplication>

#include "Exception.h"
#include "Login/Login.h"


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Login login;
    login.show();

    QObject::connect(&login, &Login::LoginSuccess, [&](){

    });
    return a.exec();
}

