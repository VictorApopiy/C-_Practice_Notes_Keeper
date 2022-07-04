#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QScopedPointer>
#include <iostream>
#include <mutex>
#include <thread>

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

private slots:

    void on_LLoginButton_clicked();
    static int *GetInstance(const int& value);

private:
    Ui::Login *ui;
    QScopedPointer <Register> m_registerform;
    QScopedPointer <Category> m_categoryform;
    QScopedPointer <DeletedNotes> m_deletednotesform;
    QScopedPointer <UserPage> m_userform;

    static int * userId;
    static std::mutex mutex;
};

#endif // LOGIN_H
