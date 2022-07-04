#ifndef NOTESINCATEGORY_H
#define NOTESINCATEGORY_H

#include <QMainWindow>
#include <QGridLayout>
#include <QTcpSocket>
#include "3rdparty/json.hpp"

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
    QTcpSocket* socket;

private slots:

    void recieveData(QString str);

private:
    Ui::NotesInCategory *ui;
    QGridLayout *lay;
};

#endif // NOTESINCATEGORY_H
