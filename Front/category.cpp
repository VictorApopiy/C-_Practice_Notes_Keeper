#include "category.h"
#include "ui_category.h"
#include "addcategory.h"
#include "popupmenubutton.h"
#include "dynamiccategory.h"
#include "deletednotes.h"
#include "userpage.h"
#include "addsavenote.h"
#include "notesincategory.h"
#include "ui_notesincategory.h"
#include "ui_addcategory.h"
#include "ui_addsavenote.h"

Category::Category(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Category)
{
    ui->setupUi(this);

    m_addcategoryform.reset(new AddCategory());
    m_addsavenote.reset(new AddSaveNote());
    m_notesincategory.reset(new NotesInCategory());

    connect(ui->CCreateCategoryButton, SIGNAL(clicked()),
            m_addcategoryform->getAddCategory().ACCategoryTitleLEdit, SLOT(clear()));
    connect(ui->CCreateCategoryButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->CCreateCategoryButton, SIGNAL(clicked()), m_addcategoryform.get(), SLOT(show()));

    connect(ui->CreateNoteButton, SIGNAL(clicked()),
            m_addsavenote->getAddSaveNote().ASNCategoryComBox, SLOT(clear()));
    connect(ui->CreateNoteButton, SIGNAL(clicked()),
            m_addsavenote->getAddSaveNote().ASNUserComBox, SLOT(clear()));
    connect(ui->CreateNoteButton, SIGNAL(clicked()),
            m_addsavenote->getAddSaveNote().ASNTitleLEdit, SLOT(clear()));
    connect(ui->CreateNoteButton, SIGNAL(clicked()),
            m_addsavenote->getAddSaveNote().ASNKeywordsTEdit, SLOT(clear()));
    connect(ui->CreateNoteButton, SIGNAL(clicked()),
            m_addsavenote->getAddSaveNote().ASNDescriptionTEdit, SLOT(clear()));
    connect(ui->CreateNoteButton, SIGNAL(clicked()), m_addsavenote.get(), SLOT(show()));
    connect(ui->CreateNoteButton, SIGNAL(clicked()), this, SLOT(close()));



    connect(m_addcategoryform->getAddCategory().ACCreateCategoryButton, SIGNAL(clicked()),
            m_addcategoryform.get(), SLOT(m_addcategoryform::onButtonSend()));
    connect(m_addcategoryform->getAddCategory().ACCreateCategoryButton, SIGNAL(clicked()), this,
            SLOT(show()));
    connect(m_addcategoryform->getAddCategory().ACCreateCategoryButton,
            SIGNAL(m_addcategoryform::sendData(QString)), this, SLOT(recieveData(QString)));
    connect(m_addcategoryform->getAddCategory().ACCreateCategoryButton, SIGNAL(clicked()),
            m_addcategoryform.get(), SLOT(close()));

    connect(m_addcategoryform->getAddCategory().ACCanselButton, SIGNAL(clicked()), this, SLOT(show()));
    connect(m_addcategoryform->getAddCategory().ACCanselButton, SIGNAL(clicked()), m_addcategoryform.get(), SLOT(close()));


    connect(m_addsavenote->getAddSaveNote().ASNCanselButton, SIGNAL(clicked()), this, SLOT(show()));
    connect(m_addsavenote->getAddSaveNote().ASNCanselButton, SIGNAL(clicked()), m_addsavenote.get(), SLOT(close()));

    connect(m_addsavenote->getAddSaveNote().ASNHomeButton, SIGNAL(clicked()), this, SLOT(show()));
    connect(m_addsavenote->getAddSaveNote().ASNHomeButton, SIGNAL(clicked()), m_addsavenote.get(), SLOT(close()));

    connect(m_addsavenote->getAddSaveNote().ASNSaveNoteButton, SIGNAL(clicked()), this, SLOT(show()));
    connect(m_addsavenote->getAddSaveNote().ASNSaveNoteButton, SIGNAL(clicked()), m_addsavenote.get(),
            SLOT(close()));


    connect(m_notesincategory->getNotesInCategory().NCHomeButton, SIGNAL(clicked()), this, SLOT(show()));
    connect(m_notesincategory->getNotesInCategory().NCHomeButton, SIGNAL(clicked()),
            m_notesincategory.get(), SLOT(close()));

    connect(m_notesincategory->getNotesInCategory().NCCreateNoteButton, SIGNAL(clicked()),
            m_addsavenote.get(), SLOT(show()));
    connect(m_notesincategory->getNotesInCategory().NCCreateNoteButton, SIGNAL(clicked()), m_notesincategory.get(), SLOT(close()));


    //    connect(ui->CDeletedNoteButton, SIGNAL(clicked()), m_notesincategory.get(), SLOT(show()));
    //    connect(ui->CDeletedNoteButton, SIGNAL(clicked()), this, SLOT(close()));
}

Category::~Category()
{
    delete ui;
}


void Category::recieveData(QString str)
{
    ui->CScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QGridLayout *lay = new QGridLayout(ui->CScrollArea);
    lay->addWidget(ui->CScrollArea, 0, 0, 1, 3);

    DynamicCategory *category = new DynamicCategory(this);
    category->setText(QString(str));
    PopupMenuButton* menu = new PopupMenuButton(category, this);
    menu ->addAction("Open");
    menu ->addAction("Edit");
    menu ->addAction("Delete");
    category->setMenu(menu);
    category->setStyleSheet(       "color: rgb(27, 43, 66);"
                                   "border: 2px solid  rgb(27, 43, 66);"
                                   "border-radius: 10px;"
                                   "Text-align:left top;font-family:yu gothic medium;font-size:20px;color:rgb(27, 43, 66);");

    category->setFixedSize(224, 103);
    lay->addWidget(category);
    //connect(category, SIGNAL(clicked()), this, SLOT(MenuOpenCategory()));
}

void Category::MenuOpenCategory()
{

}

void Category::MenuEditCategory()
{

}

void Category::MenuDeleteCategory()
{

}
