#ifndef NOTESINCATEGORY_H
#define NOTESINCATEGORY_H

#include <QMainWindow>
#include <QScopedPointer>

//class Category;
//class AddSaveNote;
//class UserPage;

namespace Ui {
class NotesInCategory;
}

class NotesInCategory : public QMainWindow
{
    Q_OBJECT

public:
    explicit NotesInCategory(QWidget *parent = nullptr);
    const Ui::NotesInCategory &getNotesInCategory() {return *ui;}
    ~NotesInCategory();

private slots:

    void recieveData(QString str);

private:
    Ui::NotesInCategory *ui;
//    Category &m_categoryform;
//    QScopedPointer <AddSaveNote> m_addsavenote;
//    QScopedPointer <UserPage> m_userform;
};

#endif // NOTESINCATEGORY_H
