#include <QApplication>
#include "login.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login Login;
    Login.show();
    return a.exec();
}
