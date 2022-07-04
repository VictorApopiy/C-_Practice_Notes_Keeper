#ifndef ADDSAVENOTE_H
#define ADDSAVENOTE_H

#include <QMainWindow>

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

private slots:
    void on_ASNSaveNoteButton_clicked();

    void CreateJson(const QString &path);

private:
    Ui::MainWindow *ui;
};
#endif // ADDSAVENOTE_H
