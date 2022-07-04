#include "addcategory.h"
#include "ui_addcategory.h"
#include "category.h"

AddCategory::AddCategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCategory)
{
    ui->setupUi(this);

//    connect(ui->ACCreateCategoryButton, SIGNAL(clicked()), this, SLOT(onButtonSend()));
//    connect(ui->ACCreateCategoryButton, SIGNAL(clicked()), m_categoryform, SLOT(show()));
//    connect(ui->ACCanselButton, SIGNAL(clicked()), m_categoryform, SLOT(show()));
//    connect(this, SIGNAL(sendData(QString)), m_categoryform, SLOT(recieveData(QString)));
}

AddCategory::~AddCategory()
{
    delete ui;
}

void AddCategory::onButtonSend()
{
    emit sendData(ui->ACCategoryTitleLEdit->text());
    close();
}

