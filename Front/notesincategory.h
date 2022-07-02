#ifndef NOTESINCATEGORY_H
#define NOTESINCATEGORY_H

#include <QMainWindow>

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
};

#endif // NOTESINCATEGORY_H
