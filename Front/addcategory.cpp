#include "addcategory.h"
#include "ui_addcategory.h"
#include "category.h"

AddCategory::AddCategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCategory)
{
    ui->setupUi(this);
    categoryform = new Category();
    connect(ui->ACCreateCategoryButton, SIGNAL(clicked()), this, SLOT(onButtonSend()));
    connect(ui->ACCreateCategoryButton, SIGNAL(clicked()), categoryform, SLOT(show()));
    connect(this, SIGNAL(sendData(QString)), categoryform, SLOT(recieveData(QString)));
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

void AddCategory::on_ACCanselButton_clicked()
{
    close();
}

