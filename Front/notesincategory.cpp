#include "notesincategory.h"
#include "ui_notesincategory.h"
#include "category.h"
#include "userpage.h"
#include "addsavenote.h"
#include "dynamiccategory.h"
#include "popupmenubutton.h"
#include <QScopedPointer>

NotesInCategory::NotesInCategory(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NotesInCategory)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(()),this,SLOT(()));
    connect(socket,SIGNAL(()),this,SLOT(()));

    ui->NCScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    lay = new QGridLayout(ui->NCScrollArea);
    lay->addWidget(ui->NCScrollArea, 0, 0, 1, 3);
    ui->NCSearchLEdit->setPlaceholderText(QString("Search"));
}

NotesInCategory::~NotesInCategory()
{
    delete ui;
}

void NotesInCategory::recieveData(QString str)
{
    QScopedPointer <AddSaveNote> m_addsavenote;
    m_addsavenote.reset(new AddSaveNote());

    DynamicCategory *note = new DynamicCategory(this);
    note->setText(QString(str));
    PopupMenuButton* menu = new PopupMenuButton(note, this);
    QAction *open;
    open = new QAction("Open", this);
    menu ->addAction(open);
    connect(open, SIGNAL(triggered()), this, SLOT(show()));

    QAction *edit;
    edit = new QAction("Edit", this);
    menu ->addAction(edit);
    connect(edit, SIGNAL(triggered()), m_addsavenote.get(), SLOT(show()));
    connect(edit, SIGNAL(triggered()), this, SLOT(close()));

    QAction *adelete;
    adelete = new QAction("Delete", this);
    menu ->addAction(adelete);
    connect(adelete, SIGNAL(triggered()), this, SLOT(show()));
    note->setMenu(menu);

    note->setStyleSheet(       "color: rgb(27, 43, 66);"
                                   "border: 2px solid  rgb(27, 43, 66);"
                                   "border-radius: 10px;"
                                   "Text-align:left;font-family:yu gothic medium;font-size:20px;color:rgb(27, 43, 66);");

    note->setFixedSize(224, 103);
    lay->addWidget(note);
}


