#include "notesincategory.h"
#include "ui_notesincategory.h"
#include "category.h"
#include "userpage.h"
#include "addsavenote.h"
#include "dynamicnote.h"
#include "popupmenutextedit.h"

NotesInCategory::NotesInCategory(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NotesInCategory)
{
    ui->setupUi(this);

    // m_addsavenote.reset(new AddSaveNote());

//     connect(ui->NCHomeButton, SIGNAL(clicked()), &m_categoryform, SLOT(show()));
//     connect(ui->NCHomeButton, SIGNAL(clicked()), this, SLOT(close()));

//     connect(ui->NCCreateNoteButton, SIGNAL(clicked()), m_addsavenote.get(), SLOT(show()));
//     connect(ui->NCCreateNoteButton, SIGNAL(clicked()), this, SLOT(close()));

    ui->NCSearchLEdit->setPlaceholderText(QString("Search"));
}

NotesInCategory::~NotesInCategory()
{
    delete ui;
}

void NotesInCategory::recieveData(QString str)
{
    ui->NCScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QGridLayout *lay = new QGridLayout(ui->NCScrollArea);
    lay->addWidget(ui->NCScrollArea, 0, 0, 1, 1);

    auto  gridLayout = new QGridLayout(ui->scrollAreaWidgetContents);
    auto  widget = new QWidget(ui->scrollAreaWidgetContents);
    widget->setObjectName(QString::fromUtf8("widget"));
    gridLayout->addWidget(widget, 0, 0, 1, 2);



    DynamicNote *deletedCategory = new DynamicNote(this);
    deletedCategory->setText(QString(str));
    PopupMenuTextEdit* menu = new PopupMenuTextEdit(deletedCategory, this);
    menu ->addAction("Open");
    menu ->addAction("Edit");
    menu ->addAction("Delete");
    //deletedCategory->setMenu(menu);
    deletedCategory->setStyleSheet(       "color: rgb(27, 43, 66);"
                                   "border: 2px solid  rgb(27, 43, 66);"
                                   "border-radius: 10px;"
                                   "Text-align:left;font-family:yu gothic medium;font-size:20px;color:rgb(27, 43, 66);");

    deletedCategory->setFixedSize(224, 103);
    gridLayout->addWidget(deletedCategory);

   // connect(deletedCategory, SIGNAL(clicked()), this, SLOT(MenuOpenCategory()));
}


