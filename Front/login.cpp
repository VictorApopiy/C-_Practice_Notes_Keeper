#include "login.h"
#include "ui_deletednotes.h"
#include "ui_userpage.h"
#include "ui_category.h"
#include "ui_login.h"
#include "register.h"
#include "category.h"
#include "deletednotes.h"
#include "userpage.h"

int* Login::userId{nullptr};

std::mutex Login::mutex;

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

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

int *Login::GetInstance(const int& value)
{
    std::lock_guard<std::mutex> lock(mutex);
    if (userId == nullptr)
    {
        userId = new int(value);
    }
    return userId;
}


void Login::on_LLoginButton_clicked()
{

}

