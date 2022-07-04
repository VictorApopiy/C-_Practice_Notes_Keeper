#include "register.h"
#include "ui_register.h"
#include "category.h"

Register::Register(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(on_RRegisterButton_clicked()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

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


struct User{
    QString m_sLogin;
    QString m_sPassword;
    User(QString _sLogin, QString _sPassword)
 {
     m_sLogin = _sLogin;
     m_sPassword = _sPassword;
 }
};

void Register::sockDisc(){
    socket->deleteLater();
}

void Register::on_RRegisterButton_clicked()
{
    Data = socket->readAll();
    User obj(ui->RLoginLEdit->text(), ui->RPasswordLEdit->text());

    QJsonObject registr;
    registr.insert("1_RequestType", "AddUser");
    registr.insert("2_Login", obj.m_sLogin);
    registr.insert("3_Password", obj.m_sPassword);
    QJsonDocument document;
    document.setObject(registr);
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
        else if(msg.at(0) == "NO_SUCH_USER"){
            msgBox.setText("No such user");
        }
        else if(msg.at(0) == "UNEXPECTED_ERROR"){
            msgBox.setText("Unexpected error");
        }
    }
}
