#include "userpage.h"
#include "ui_userpage.h"
#include "category.h"
#include "login.h"

UserPage::UserPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserPage)
{
    ui->setupUi(this);
}

UserPage::~UserPage()
{
    delete ui;
}

void UserPage::on_UPLogOutButton_clicked()
{
    Login* w = new Login();
    w->show();
    close();
}

