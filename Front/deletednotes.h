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
    ~DeletedNotes();

private slots:
    void on_DNHomeButton_clicked();

    void on_DNUserButton_clicked();

    void recieveData(QString str);

private:
    Ui::DeletedNotes *ui;
};

#endif // DELETEDNOTES_H
