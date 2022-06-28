#ifndef ADDCATEGORY_H
#define ADDCATEGORY_H

#include <QDialog>
#include "category.h"

namespace Ui {
class AddCategory;
}

class AddCategory : public QDialog
{
    Q_OBJECT

public:
    explicit AddCategory(QWidget *parent = nullptr);
    ~AddCategory();

signals:
    void sendData(QString str);

private slots:
    void onButtonSend();

    void on_ACCanselButton_clicked();

private:
    Ui::AddCategory *ui;
    Category *categoryform;
};

#endif // ADDCATEGORY_H
