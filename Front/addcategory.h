#ifndef ADDCATEGORY_H
#define ADDCATEGORY_H

#include <QDialog>
#include <QTcpSocket>
#include <QScopedPointer>
#include <iostream>
#include <mutex>
#include <thread>
#include <QByteArray>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include "3rdparty/json.hpp"

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
    QTcpSocket* socket;
    int categoryId;

public slots:
    void sockDisc();

signals:
    void sendData(QString str);

private slots:
    void onButtonSend();

    void on_ACCreateCategoryButton_clicked();

private:
    Ui::AddCategory *ui;
    QByteArray Data;
    int ccount = 0;
    int ucount = 0;
};

#endif // ADDCATEGORY_H
