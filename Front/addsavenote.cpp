#include "addsavenote.h"
#include "ui_addsavenote.h"
#include <QtCore>
#include <iostream>
#include <QIODevice>
#include <string>
#include <vector>
#include <memory>
#include <QRegularExpression>
#include <QStringConverter>
#include "notesincategory.h"
#include "category.h"
#include "addcategory.h"
#include <QMessageBox>


AddSaveNote::AddSaveNote(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(on_ASNSaveNoteButton_clicked()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));

    ui->ASNKeywordsTEdit->setPlaceholderText(QString("Record format: Keyword1;Keyword2;Keyword3"));
}

AddSaveNote::~AddSaveNote()
{
    delete ui;
}

void AddSaveNote::sockDisc(){
    socket->deleteLater();
}

struct AddNote
{
    int m_iNoteId;
    int m_iCategoryId;
    std::vector <QString> m_vsKeywords;


    AddNote( int _iNoteId, int _iCategoryId, std::vector <QString> _vsKeywords)
    {
        m_iNoteId = _iNoteId;
        m_iCategoryId = _iCategoryId;
        m_vsKeywords = _vsKeywords;
    }
};

struct SetHeader
{
    int m_iNoteId;
    QString m_sHeader;


    SetHeader( int _iNoteId, QString _sHeader)
    {
        m_iNoteId = _iNoteId;
        m_sHeader = _sHeader;
    }
};

struct SetText
{
    int m_iNoteId;
    QString m_sText;


    SetText(int _iNoteId, QString _sText)
    {
        m_iNoteId = _iNoteId;
        m_sText = _sText;
    }
};

void AddSaveNote::on_ASNSaveNoteButton_clicked()
{
    Data = socket->readAll();
    QRegularExpression rx("(\\\n|\\:|\\;)");
    QString sKeywordsText = ui->ASNKeywordsTEdit->toPlainText();
    QStringList myStringList = sKeywordsText.split(rx);
    std::vector <QString> vsKeywords;
    QJsonObject keywords;

    for(int i = 0; i < myStringList.size(); ++i)
    {
       vsKeywords.push_back(myStringList[i].toUtf8().constData());
       keywords.insert( QString::number(i), myStringList[i].toUtf8().constData());
    }

    ++ncount;
    ++ccount;

    AddNote objAN(ncount, ccount, vsKeywords);


    QJsonObject AddNote;
    AddNote.insert( "1_RequestType", "AddNote");
    AddNote.insert( "2_IdNote", objAN.m_iNoteId);
    AddNote.insert( "3_IdCategory", objAN.m_iCategoryId);
    AddNote.insert( "4_Keywords", keywords);

    QJsonDocument document;
    document.setObject( AddNote );
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
            int iNoteId = std::stoi(msg.at(1));
            SetHeader objH( iNoteId, ui->ASNTitleLEdit->text());

            SetText objT( iNoteId, ui->ASNDescriptionTEdit->toPlainText());
            QJsonObject SetHeader;
            SetHeader.insert( "1_RequestType", "SetHeader");
            SetHeader.insert( "2_IdNote", objH.m_iNoteId);
            SetHeader.insert( "3_Header", objH.m_sHeader);

            QJsonDocument document;
            document.setObject( SetHeader );
            QByteArray bytes = document.toJson( QJsonDocument::Indented );
            socket->write(bytes);
            socket->waitForBytesWritten(500);
            Data = socket->readAll();
            nlohmann::json k;
            k = nlohmann::json::parse(QString(Data).toStdString());

            for (nlohmann::json::iterator it = k.begin(); it != k.end(); ++it) {
                    msg.push_back(it.value());
            }
            if(msg.at(0) == "SUCCESS"){
                msgBox.setText("Success");
            }
            else if(msg.at(0) == "INVALID_INPUT_DATA"){
                msgBox.setText("Invalid input data");
            }
            else if(msg.at(0) == "NO_SUCH_NOTE"){
                msgBox.setText("No such note");
            }
            else if(msg.at(0) == "UNEXPECTED_ERROR"){
                msgBox.setText("Unexpected error");
            }
            QJsonObject SetText;
            SetText.insert( "1_RequestType", "SetText");
            SetText.insert( "2_IdNote", objT.m_iNoteId);
            SetText.insert( "3_Text", objT.m_sText);

            QJsonDocument document1;
            document1.setObject( SetText );
            QByteArray bytes1 = document1.toJson( QJsonDocument::Indented );
            socket->write(bytes1);
            socket->waitForBytesWritten(500);
            Data = socket->readAll();
            nlohmann::json l;
            l = nlohmann::json::parse(QString(Data).toStdString());

            for (nlohmann::json::iterator it = l.begin(); it != l.end(); ++it) {
                    msg.push_back(it.value());
            }
            if(msg.at(0) == "SUCCESS"){
                msgBox.setText("Success");
            }
            else if(msg.at(0) == "INVALID_INPUT_DATA"){
                msgBox.setText("Invalid input data");
            }
            else if(msg.at(0) == "NO_SUCH_NOTE"){
                msgBox.setText("No such note");
            }
            else if(msg.at(0) == "UNEXPECTED_ERROR"){
                msgBox.setText("Unexpected error");
            }

        }
        else if(msg.at(0) == "INVALID_INPUT_DATA"){
            msgBox.setText("Invalid input data");
        }
        else if(msg.at(0) == "NO_SUCH_CATEGORY"){
            msgBox.setText("No such category");
        }
        else if(msg.at(0) == "UNEXPECTED_ERROR"){
            msgBox.setText("Unexpected error");
        }
    }
    ui->ExplanationLabel->clear();
    if(ui->ASNTitleLEdit->text()=="")
    {
        ui->ExplanationLabel->setText(ui->ExplanationLabel->text() + "write title");
    }
    else if(ui->ASNDescriptionTEdit->document()->isEmpty())
    {
        ui->ExplanationLabel->setText(ui->ExplanationLabel->text() + "write description");
    }
    else if(ui->ASNKeywordsTEdit->document()->isEmpty())
    {
        ui->ExplanationLabel->setText(ui->ExplanationLabel->text() + "write keywords");
    }
    else if(ui->ASNCategoryComBox->currentText()=="Select category")
    {
        ui->ExplanationLabel->setText(ui->ExplanationLabel->text() + "select category");
    }

}

