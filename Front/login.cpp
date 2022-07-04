#include "login.h"
#include "ui_deletednotes.h"
#include "ui_userpage.h"
#include "ui_category.h"
#include "ui_login.h"
#include "register.h"
#include "category.h"
#include "deletednotes.h"
#include "userpage.h"



int* Login::user_Id{nullptr};

std::mutex Login::mutex;

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(on_LLoginButton_clicked()),this,SLOT(on_LLoginButton_clicked()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
    socket->connectToHost("127.0.0.1",5555);

    m_registerform.reset(new Register());
    m_categoryform.reset(new Category());
    m_deletednotesform.reset(new DeletedNotes());
    m_userform.reset(new UserPage());

    connect(ui->LRegisterButton, SIGNAL(clicked()), m_registerform.get(), SLOT(show()));
    connect(ui->LRegisterButton, SIGNAL(clicked()), this, SLOT(close()));

    connect(ui->LLoginButton, SIGNAL(clicked()), m_categoryform.get(), SLOT(show()));
    connect(ui->LLoginButton, SIGNAL(clicked()), this, SLOT(close()));


    connect(m_deletednotesform->getDeletedNotes().DNHomeButton, SIGNAL(clicked()), m_categoryform.get(), SLOT(show()));
    connect(m_deletednotesform->getDeletedNotes().DNHomeButton, SIGNAL(clicked()), m_deletednotesform.get(), SLOT(close()));

    connect(m_deletednotesform->getDeletedNotes().DNUserButton, SIGNAL(clicked()), m_userform.get(), SLOT(show()));
    connect(m_deletednotesform->getDeletedNotes().DNUserButton, SIGNAL(clicked()), m_deletednotesform.get(), SLOT(close()));


    connect(m_userform->getUserPage().UPLogOutButton, SIGNAL(clicked()), this, SLOT(show()));
    connect(m_userform->getUserPage().UPLogOutButton, SIGNAL(clicked()), m_userform.get(), SLOT(close()));

    connect(m_userform->getUserPage().UPHomeButton, SIGNAL(clicked()), m_categoryform.get(), SLOT(show()));
    connect(m_userform->getUserPage().UPHomeButton, SIGNAL(clicked()), m_userform.get(), SLOT(close()));


    connect(m_categoryform->getCategory().CDeletedNoteButton, SIGNAL(clicked()), m_deletednotesform.get(), SLOT(show()));
    connect(m_categoryform->getCategory().CDeletedNoteButton, SIGNAL(clicked()), m_categoryform.get(), SLOT(close()));

    connect(m_categoryform->getCategory().CUserButton, SIGNAL(clicked()), m_userform.get(), SLOT(show()));
    connect(m_categoryform->getCategory().CUserButton, SIGNAL(clicked()), m_categoryform.get(), SLOT(close()));


    ui->LLoginLEdit->setPlaceholderText(QString("Login"));
    ui->LPasswordLEdit->setPlaceholderText(QString("Password"));
}

Login::~Login()
{
    delete ui;
}

struct User{
    QString m_sLogin;
    QString m_sPassword;
    User(QString _sLogin, QString _sPassword)
 {
     m_sLogin = _sLogin;
     m_sPassword = _sPassword;
 }
};

int *Login::GetInstance(const int& value)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (user_Id == nullptr)
    {
        user_Id = new int(value);
    }
    return user_Id;
}

void Login::sockDisc(){
    socket->deleteLater();
}

void Login::on_LLoginButton_clicked()
{
    Data = socket->readAll();
    User obj( ui->LLoginLEdit->text(), ui->LPasswordLEdit->text());

    QJsonObject login;
    login.insert("1_RequestType", "GetUserId");
    login.insert("2_Login", obj.m_sLogin);
    login.insert("3_Password", obj.m_sPassword);
    QJsonDocument document;
    document.setObject( login );
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
            int iUserId = std::stoi(msg.at(1));
            userId = iUserId;
        }
        else if(msg.at(0) == "INVALID_INPUT_DATA"){
            msgBox.setText("Invalid input data");
        }
        else if(msg.at(0) == "UNEXPECTED_ERROR"){
            msgBox.setText("Unexpected error");
        }
    }
}

