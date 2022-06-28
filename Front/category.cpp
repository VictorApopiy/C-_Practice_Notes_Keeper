#include "category.h"
#include "ui_category.h"
#include "addcategory.h"
#include "popupmenu.h"
#include "dynamiccategory.h"
#include "deletednotes.h"
#include "userpage.h"
#include "addsavenote.h"
#include "notesincategory.h"

Category::Category(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Category)
{
    ui->setupUi(this);
}

Category::~Category()
{
    delete ui;
}


void Category::recieveData(QString str)
{
    ui->CScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QGridLayout *lay = new QGridLayout(ui->CScrollArea);
    lay->addWidget(ui->CScrollArea, 0, 0, 1, 1);

    auto  gridLayout = new QGridLayout(ui->scrollAreaWidgetContents);
    auto  widget = new QWidget(ui->scrollAreaWidgetContents);
    widget->setObjectName(QString::fromUtf8("widget"));
    gridLayout->addWidget(widget, 0, 0, 1, 3);



    DynamicCategory *category = new DynamicCategory(this);
    category->setText(QString(str));
    PopupMenu* menu = new PopupMenu(category, this);
    menu ->addAction("Open");
    menu ->addAction("Edit");
    menu ->addAction("Delete");
    category->setMenu(menu);
    category->setStyleSheet(       "color: rgb(27, 43, 66);"
                                   "border: 2px solid  rgb(27, 43, 66);"
                                   "border-radius: 10px;"
                                   "padding: 1px 18px 1px 3px;"
                                   "min-width: 6em;}"
                                   "Text-align:left;font-family:yu gothic medium;font-size:20px;color:rgb(27, 43, 66);");

    category->setFixedSize(224, 103);
    gridLayout->addWidget(category);

    //connect(category, SIGNAL(clicked()), this, SLOT(MenuOpenCategory()));
}

void Category::on_CCreateCategoryButton_clicked()
{
    AddCategory* w = new AddCategory();
    w->show();
    close();
}


void Category::on_CDeletedNoteButton_clicked()
{
    DeletedNotes* w = new DeletedNotes();
    w->show();
    close();
}


void Category::on_CUserButton_clicked()
{
    UserPage* w = new UserPage();
    w->show();
    close();
}


void Category::on_CreateNoteButton_clicked()
{
    AddSaveNote* w = new AddSaveNote();
    w->show();
    close();
}

void Category::MenuOpenCategory()
{
    NotesInCategory* w = new NotesInCategory();
    w->show();
    close();
}

void Category::MenuEditCategory()
{
    NotesInCategory* w = new NotesInCategory();
    w->show();
    close();
}

void Category::MenuDeleteCategory()
{

}
