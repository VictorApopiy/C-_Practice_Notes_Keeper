#include "login.h"
#include "ui_login.h"
#include "register.h"
#include "category.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->LLoginLEdit->setPlaceholderText(QString("Login"));
    ui->LPasswordLEdit->setPlaceholderText(QString("Password"));
}

Login::~Login()
{
    delete ui;
}


void Login::on_LRegisterButton_clicked()
{
    Register* w = new Register();
    w->show();
    close();
}


void Login::on_LLoginButton_clicked()
{
    Category* w = new Category();
    w->show();
    close();
}

