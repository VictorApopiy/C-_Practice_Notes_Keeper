#include "addsavenote.h"
#include "ui_addsavenote.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

struct Note
{
    QString sTitle;
    QString sDescription;
    vector <QString> vsKeywords;
    QString sCategory;
    QString sAccessUser;

    Note( QString _sTitle, QString _sDescription, vector <QString> _vsKeywords,
            QString _sCategory, QString _sAccessUser)
    {
        sTitle = _sTitle;
        sDescription = _sDescription;
        vsKeywords = _vsKeywords;
        sCategory = _sCategory;
        sAccessUser = _sAccessUser;
    }
};

void MainWindow::CreateJson(const QString &path)
{
    QRegularExpression rx("(\\\n|\\:|\\;)");
    QString sKeywordsText = ui->KeywordsTEdit->toPlainText();
    QStringList myStringList = sKeywordsText.split(rx);
    vector <QString> vsKeywords;
    QJsonObject keywords;
    for(int i=0;i<myStringList.size();i++)
    {
       vsKeywords.push_back(myStringList[i].toUtf8().constData());
       keywords.insert( QString::number(i), myStringList[i].toUtf8().constData());
    }

    Note obj( ui->TitleLEdit->text(), ui->DescriptionTEdit->toPlainText(),
              vsKeywords, ui->CategoryComBox->currentText(),
              ui->UserComBox->currentText());

    QJsonObject note;
    note.insert( "title", obj.sTitle);
    note.insert( "description", obj.sDescription);
    note.insert( "keywords", keywords);
    note.insert( "category", obj.sCategory);
    note.insert( "access user", obj.sAccessUser);

    QJsonObject content;
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
        cout << "file open failed: " << path.toStdString() << endl;
    }
}


void ReadJson(const QString &path)
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
            cout << "fromJson failed: " << jsonError.errorString().toStdString() << endl;
            return ;
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


void MainWindow::on_SaveNoteButton_clicked()
{
    ui->ExplanationLabel->clear();
    if(ui->TitleLEdit->text()=="")
    {
        ui->ExplanationLabel->setText(ui->ExplanationLabel->text() + "write title");
    }
    else if(ui->DescriptionTEdit->document()->isEmpty())
    {
        ui->ExplanationLabel->setText(ui->ExplanationLabel->text() + "write description");
    }
    else if(ui->KeywordsTEdit->document()->isEmpty())
    {
        ui->ExplanationLabel->setText(ui->ExplanationLabel->text() + "write keywords");
    }
    else if(ui->CategoryComBox->currentText()=="Select category")
    {
        ui->ExplanationLabel->setText(ui->ExplanationLabel->text() + "select category");
    }
    else{
        QString path = "D:/Notes Keeper/test.json";
        CreateJson( path );
        ReadJson( path );
    }

}

