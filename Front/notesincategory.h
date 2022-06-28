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
    ~NotesInCategory();

private slots:
    void on_NCHomeButton_clicked();

    void on_NCUserButton_clicked();

    void on_NCCreateNoteButton_clicked();

    void recieveData(QString str);

private:
    Ui::NotesInCategory *ui;
};

#endif // NOTESINCATEGORY_H
