#include "addsavenote.h"
#include "ui_addsavenote.h"
#include "category.h"


AddSaveNote::AddSaveNote(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->ASNKeywordsTEdit->setPlaceholderText(QString("Record format: Keyword1;Keyword2;Keyword3"));
}

AddSaveNote::~AddSaveNote()
{
    delete ui;
}

struct Note
{
    QString m_sTitle;
    QString m_sDescription;
    std::vector <QString> m_vsKeywords;
    QString m_sCategory;
    QString m_sAccessUser;

    Note( QString _sTitle, QString _sDescription, std::vector <QString> _vsKeywords,
            QString _sCategory, QString _sAccessUser)
    {
        m_sTitle = _sTitle;
        m_sDescription = _sDescription;
        m_vsKeywords = _vsKeywords;
        m_sCategory = _sCategory;
        m_sAccessUser = _sAccessUser;
    }
};

void AddSaveNote::CreateJson(const QString &path)
{
    QRegularExpression rx("(\\\n|\\:|\\;)");
    QString sKeywordsText = ui->ASNKeywordsTEdit->toPlainText();
    QStringList myStringList = sKeywordsText.split(rx);
    std::vector <QString> vsKeywords;
    QJsonObject keywords;
    QString sRequestType = "Create a note";

    for(int i = 0; i < myStringList.size(); ++i)
    {
       vsKeywords.push_back(myStringList[i].toUtf8().constData());
       keywords.insert( QString::number(i), myStringList[i].toUtf8().constData());
    }

    Note obj( ui->ASNTitleLEdit->text(), ui->ASNDescriptionTEdit->toPlainText(),
              vsKeywords, ui->ASNCategoryComBox->currentText(),
              ui->ASNUserComBox->currentText());

    QJsonObject note;
    note.insert( "title", obj.m_sTitle);
    note.insert( "description", obj.m_sDescription);
    note.insert( "keywords", keywords);
    note.insert( "category", obj.m_sCategory);
    note.insert( "access user", obj.m_sAccessUser);

    QJsonObject content;
    content.insert( "Request type", sRequestType);
    content.insert( "Note", note);

    QJsonDocument document;
    document.setObject( content );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );
    QFile file( path );
    if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
    {
        QTextStream iStream( &file );
        iStream << bytes;
        file.close();
    }
    else
    {
        std::cout << "file open failed: " << path.toStdString() << std::endl;
    }
}


bool ReadJson(const QString &path)
{
    QFile file( path );
    if( file.open( QIODevice::ReadOnly ) )
    {
        QByteArray bytes = file.readAll();
        file.close();

        QJsonParseError jsonError;
        QJsonDocument document = QJsonDocument::fromJson( bytes, &jsonError );
        if( jsonError.error != QJsonParseError::NoError )
        {
           std:: cout << "fromJson failed: " << jsonError.errorString().toStdString() << std::endl;
            return false;
        }
        if( document.isObject() )
        {
            QJsonObject jsonObj = document.object();
            QStringList notes;
            notes << "note";
            for( const auto &note: notes )
            {
                if( jsonObj.contains( note ) )
                {
                    QJsonObject obj = jsonObj.value( note ).toObject();
                    QStringList keys = obj.keys();
                    for( const auto &key: keys )
                    {
                        auto value = obj.take( key );
                        qDebug() << key << " : " << value.toString();
                    }
                }
            }
        }
    }
}


void AddSaveNote::on_ASNSaveNoteButton_clicked()
{
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
    else
    {
        QString path = "test.json";
        CreateJson( path );
        ReadJson( path );
    }

}


void AddSaveNote::on_ASNCanselButton_clicked()
{
    Category* w = new Category();
    w->show();
    close();
}


void AddSaveNote::on_ASNHomeButton_clicked()
{
    Category* w = new Category();
    w->show();
    close();
}

