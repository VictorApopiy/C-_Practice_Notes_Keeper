#include "userpage.h"
#include "ui_userpage.h"
#include "category.h"
#include "login.h"

UserPage::UserPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserPage)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(()),this,SLOT(()));
    connect(socket,SIGNAL(()),this,SLOT(()));

}

UserPage::~UserPage()
{
    delete ui;
}



