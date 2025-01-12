#include "Login/Login.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Login login;
    login.show();

    return a.exec();
}
