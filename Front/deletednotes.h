#ifndef DELETEDNOTES_H
#define DELETEDNOTES_H

#include <QMainWindow>
#include <QGridLayout>
#include <QTcpSocket>
#include "3rdparty/json.hpp"

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
    QTcpSocket* socket;

private slots:
    void recieveData(QString str);

private:
    Ui::DeletedNotes *ui;
    QGridLayout *lay;
};

#endif // DELETEDNOTES_H
