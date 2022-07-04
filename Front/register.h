#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QScopedPointer>
#include <QtCore>
#include <iostream>
#include <QIODevice>
#include <string>
#include <vector>
#include <memory.h>
#include <QRegularExpression>
#include <QStringConverter>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QString>
#include "3rdparty/json.hpp"

class Category;

namespace Ui {
class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();
    QTcpSocket* socket;
    int userId;

public slots:

    void sockDisc();

private slots:
    void on_RRegisterButton_clicked();


private:
    Ui::Register *ui;
    QScopedPointer <Category> m_categoryform;
        QByteArray Data;
};

#endif // REGISTER_H
