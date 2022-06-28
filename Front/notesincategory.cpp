#include "notesincategory.h"
#include "ui_notesincategory.h"
#include "category.h"
#include "userpage.h"
#include "addsavenote.h"
#include "dynamicnote.h"
#include "popupmenu.h"

NotesInCategory::NotesInCategory(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NotesInCategory)
{
    ui->setupUi(this);
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
    PopupMenu* menu = new PopupMenu(deletedCategory, this);
    menu ->addAction("Open");
    menu ->addAction("Edit");
    menu ->addAction("Delete");
    //deletedCategory->setMenu(menu);
    deletedCategory->setStyleSheet(       "color: rgb(27, 43, 66);"
                                   "border: 2px solid  rgb(27, 43, 66);"
                                   "border-radius: 10px;"
                                   "padding: 1px 18px 1px 3px;"
                                   "min-width: 6em;}"
                                   "Text-align:left;font-family:yu gothic medium;font-size:20px;color:rgb(27, 43, 66);");

    deletedCategory->setFixedSize(224, 103);
    gridLayout->addWidget(deletedCategory);

   // connect(deletedCategory, SIGNAL(clicked()), this, SLOT(MenuOpenCategory()));
}

void NotesInCategory::on_NCHomeButton_clicked()
{
    Category* w = new Category();
    w->show();
    close();
}


void NotesInCategory::on_NCUserButton_clicked()
{
    UserPage* w = new UserPage();
    w->show();
    close();
}


void NotesInCategory::on_NCCreateNoteButton_clicked()
{
    AddSaveNote* w = new AddSaveNote();
    w->show();
    close();
}

