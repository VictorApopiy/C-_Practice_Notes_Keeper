#include "register.h"
#include "ui_register.h"
#include "category.h"

Register::Register(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    m_categoryform.reset(new Category());

    connect(ui->RRegisterButton, SIGNAL(clicked()), m_categoryform.get(), SLOT(show()));
    connect(ui->RRegisterButton, SIGNAL(clicked()), this, SLOT(close()));

    ui->RLoginLEdit->setPlaceholderText(QString("Login"));
    ui->RPasswordLEdit->setPlaceholderText(QString("Create password"));
}

Register::~Register()
{
    delete ui;
}


