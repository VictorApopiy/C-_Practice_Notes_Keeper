#ifndef DELETEDNOTES_H
#define DELETEDNOTES_H

#include <QMainWindow>

namespace Ui {
class DeletedNotes;
}

class DeletedNotes : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeletedNotes(QWidget *parent = nullptr);
    const Ui::DeletedNotes &getDeletedNotes() {return *ui;}
    ~DeletedNotes();

private slots:
    void recieveData(QString str);

private:
    Ui::DeletedNotes *ui;
};

#endif // DELETEDNOTES_H
