#ifndef ADDSAVENOTE_H
#define ADDSAVENOTE_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include "3rdparty/json.hpp"
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class AddSaveNote : public QMainWindow
{
    Q_OBJECT

public:
    AddSaveNote(QWidget *parent = nullptr);
    const Ui::MainWindow &getAddSaveNote() {return *ui;}
    ~AddSaveNote();
    QTcpSocket* socket;

public slots:
    void sockDisc();

private slots:
    void on_ASNSaveNoteButton_clicked();

private:
    Ui::MainWindow *ui;
    QByteArray Data;
    int ncount = 0;
    int ccount = 0;

};
#endif // ADDSAVENOTE_H
