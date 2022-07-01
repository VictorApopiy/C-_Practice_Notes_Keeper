#ifndef ADDCATEGORY_H
#define ADDCATEGORY_H

#include <QDialog>
#include <QScopedPointer>

//class Category;

namespace Ui {
class AddCategory;
}

class AddCategory : public QDialog
{
    Q_OBJECT

public:
    explicit AddCategory(QWidget *parent = nullptr);
    const Ui::AddCategory &getAddCategory() {return *ui;}
    ~AddCategory();

signals:
    void sendData(QString str);

private slots:
    void onButtonSend();

private:
    Ui::AddCategory *ui;
//    QScopedPointer <Category> m_categoryform;
};

#endif // ADDCATEGORY_H
