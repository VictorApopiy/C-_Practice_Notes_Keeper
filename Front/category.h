#ifndef CATEGORY_H
#define CATEGORY_H

#include <QMainWindow>
#include <QMenuBar>
#include <QScopedPointer>
#include <QGridLayout>
#include <QTcpSocket>
#include "3rdparty/json.hpp"

class AddCategory;
class AddSaveNote;
class NotesInCategory;

namespace Ui {
class Category;
}

class Category : public QMainWindow
{
    Q_OBJECT

public:
    explicit Category(QWidget *parent = nullptr);
    const Ui::Category &getCategory() {return *ui;}
    ~Category();
    QTcpSocket* socket;

private slots:
    void MenuOpenCategory();

    void MenuEditCategory();

    void MenuDeleteCategory();

    void on_CCreateCategoryButton_clicked();

    void recieveData(QString str);

private:
    Ui::Category *ui;
    QScopedPointer <AddCategory> m_addcategoryform;
    QScopedPointer <AddSaveNote> m_addsavenote;
    QScopedPointer <NotesInCategory> m_notesincategory;
    QGridLayout *lay;
    QString categoryname;
};

#endif // CATEGORY_H
