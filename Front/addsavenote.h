#ifndef ADDSAVENOTE_H
#define ADDSAVENOTE_H

#include <QMainWindow>
#include <QtCore>
#include <iostream>
#include <QIODevice>
#include <string>
#include <vector>
#include <memory.h>
#include <QRegularExpression>
#include <QStringConverter>
#include "notesincategory.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class AddSaveNote : public QMainWindow
{
    Q_OBJECT

public:
    AddSaveNote(QWidget *parent = nullptr);
    ~AddSaveNote();

private slots:
    void on_ASNSaveNoteButton_clicked();
    void CreateJson(const QString &path);

    void on_ASNCanselButton_clicked();

    void on_ASNHomeButton_clicked();

private:
    Ui::MainWindow *ui;
    NotesInCategory *notesInCategory;
};
#endif // ADDSAVENOTE_H
