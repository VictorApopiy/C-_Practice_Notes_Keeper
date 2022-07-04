#include "deletednotes.h"
#include "ui_deletednotes.h"
#include "category.h"
#include "userpage.h"
#include "dynamicnote.h"
#include "popupmenutextedit.h"

DeletedNotes::DeletedNotes(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeletedNotes)
{
    ui->setupUi(this);

}

DeletedNotes::~DeletedNotes()
{
    delete ui;
}

void DeletedNotes::recieveData(QString str)
{
    ui->DNScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QGridLayout *lay = new QGridLayout(ui->DNScrollArea);
    lay->addWidget(ui->DNScrollArea, 0, 0, 1, 1);

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
