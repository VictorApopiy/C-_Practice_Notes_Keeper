#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QScopedPointer>
#include <iostream>
#include <mutex>
#include <thread>
#include <QByteArray>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include "3rdparty/json.hpp"

class Register;
class Category;
class DeletedNotes;
class UserPage;

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    QTcpSocket* socket;
    int userId;

public slots:
    void sockDisc();

private slots:

    void on_LLoginButton_clicked();
    static int *GetInstance(const int& value);

private:
    Ui::Login *ui;
    QScopedPointer <Register> m_registerform;
    QScopedPointer <Category> m_categoryform;
    QScopedPointer <DeletedNotes> m_deletednotesform;
    QScopedPointer <UserPage> m_userform;

    static int * user_Id;
    static std::mutex mutex;
    QByteArray Data;
};

#endif // LOGIN_H
