#include "deletednotes.h"
#include "ui_deletednotes.h"
#include "category.h"
#include "userpage.h"
#include "dynamiccategory.h"
#include "popupmenubutton.h"

DeletedNotes::DeletedNotes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeletedNotes)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(()),this,SLOT(()));
    connect(socket,SIGNAL(()),this,SLOT(()));

    ui->DNScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    lay = new QGridLayout(ui->DNScrollArea);
    lay->addWidget(ui->DNScrollArea, 0, 0, 1, 3);
}

DeletedNotes::~DeletedNotes()
{
    delete ui;
}

void DeletedNotes::recieveData(QString str)
{

    DynamicCategory *deletedNote = new DynamicCategory(this);
    deletedNote->setText(QString(str));
    PopupMenuButton* menu = new PopupMenuButton(deletedNote, this);
    QAction *restore;
    restore = new QAction("Restor", this);
    menu ->addAction(restore);
    connect(restore, SIGNAL(triggered()), this, SLOT(show()));
    deletedNote->setMenu(menu);

    deletedNote->setStyleSheet(       "color: rgb(27, 43, 66);"
                                   "border: 2px solid  rgb(27, 43, 66);"
                                   "border-radius: 10px;"
                                   "Text-align:left;font-family:yu gothic medium;font-size:20px;color:rgb(27, 43, 66);");

    deletedNote->setFixedSize(224, 103);
    lay->addWidget(deletedNote);

}
