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


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_SaveNoteButton_clicked();
    void CreateJson(const QString &path);

private:
    Ui::MainWindow *ui;
};
#endif // ADDSAVENOTE_H
