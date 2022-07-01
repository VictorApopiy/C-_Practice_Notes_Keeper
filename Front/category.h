#ifndef CATEGORY_H
#define CATEGORY_H

#include <QMainWindow>
#include <QMenuBar>
#include <QScopedPointer>

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

private slots:
    void recieveData(QString str);

    void MenuOpenCategory();

    void MenuEditCategory();

    void MenuDeleteCategory();

private:
    Ui::Category *ui;
    QScopedPointer <AddCategory> m_addcategoryform;
    QScopedPointer <AddSaveNote> m_addsavenote;
    QScopedPointer <NotesInCategory> m_notesincategory;
};

#endif // CATEGORY_H
