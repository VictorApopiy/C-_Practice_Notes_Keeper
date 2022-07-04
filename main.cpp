#include <QCoreApplication>
#include "myserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CMyServer Server;
    Server.startServer();

    return a.exec();
}
