#include "register.h"
#include "ui_register.h"
#include "category.h"

Register::Register(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    ui->RLoginLEdit->setPlaceholderText(QString("Login"));
    ui->RPasswordLEdit->setPlaceholderText(QString("Create password"));
}

Register::~Register()
{
    delete ui;
}

void Register::on_RRegisterButton_clicked()
{
    Category* w = new Category();
    w->show();
    close();
}

