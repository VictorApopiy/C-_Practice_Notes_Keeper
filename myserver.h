#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QString>
#include <QByteArray>
#include <QByteArrayView>
#include <QtCore>
#include <iostream>
#include <QIODevice>
#include <string>
#include <vector>
#include <memory.h>
#include <QRegularExpression>
#include <QStringConverter>

class myserver: public QTcpServer{
    Q_OBJECT
public:
    myserver();
    ~myserver();

    QTcpSocket* socket;
    QByteArray Data;

    QJsonDocument doc;
    QJsonParseError docError;

    QByteArray res;

    QSqlDatabase db;

public slots:
    void startServer();
    void incomingConnection(qintptr pisocketDescriptor);
    void sockReady();
    void sockDisc();
};

#endif // MYSERVER_H
