#include "addcategory.h"
#include "ui_addcategory.h"
#include "category.h"
#include "login.h"
#include "register.h"


AddCategory::AddCategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCategory)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(on_ACCreateCategoryButton_clicked()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
}

AddCategory::~AddCategory()
{
    delete ui;
}

void AddCategory::sockDisc(){
    socket->deleteLater();
}

void AddCategory::onButtonSend()
{
    emit sendData(ui->ACCategoryTitleLEdit->text());
    close();
}

struct AddCategorStr
{
    int m_iCategoryId;
    int m_iUserId;
    QString m_sCategoryTitle;


    AddCategorStr( int _iCategoryId, int _iUserId, QString _sCategoryTitle)
    {
        m_iCategoryId = _iCategoryId;
        m_iUserId = _iUserId;
        m_sCategoryTitle = _sCategoryTitle;
    }
};

void AddCategory::on_ACCreateCategoryButton_clicked()
{
    Data = socket->readAll();

    ++ccount;
    ++ucount;

    AddCategorStr objAC(ccount, ucount, ui->ACCategoryTitleLEdit->text());


    QJsonObject AddCategoryJ;
    AddCategoryJ.insert( "1_RequestType", "CreateCategory");
    AddCategoryJ.insert( "2_IdCategory", objAC.m_iCategoryId);
    AddCategoryJ.insert( "3_IdUser", objAC.m_iUserId);
    AddCategoryJ.insert( "4_CategoryTitle", objAC.m_sCategoryTitle);

    QJsonDocument document;
    document.setObject( AddCategoryJ );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );
    socket->write(bytes);
    socket->waitForBytesWritten(500);
    if(socket->waitForConnected(500)){
        socket->waitForReadyRead(500);
        Data = socket->readAll();
        std::vector <std::string> msg;
        QMessageBox msgBox;

        nlohmann::json j;
        j = nlohmann::json::parse(QString(Data).toStdString());

        for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
                msg.push_back(it.value());
        }
        if(msg.at(0) == "SUCCESS"){
            int iCategoryId = std::stoi(msg.at(1));
            categoryId = iCategoryId;
        }
        else if(msg.at(0) == "NO_SUCH_USER"){
            msgBox.setText("No such user");
        }
        else if(msg.at(0) == "INVALID_INPUT_DATA"){
            msgBox.setText("Invalid input data");
        }
        else if(msg.at(0) == "UNEXPECTED_ERROR"){
            msgBox.setText("Unexpected error");
        }
    }
}

