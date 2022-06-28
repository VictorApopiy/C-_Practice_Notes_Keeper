#ifndef CATEGORY_H
#define CATEGORY_H

#include <QMainWindow>
#include <QMenuBar>

namespace Ui {
class Category;
}

class Category : public QMainWindow
{
    Q_OBJECT

public:
    explicit Category(QWidget *parent = nullptr);
    ~Category();

private slots:
    void recieveData(QString str);

    void on_CCreateCategoryButton_clicked();

    void on_CDeletedNoteButton_clicked();

    void on_CUserButton_clicked();

    void on_CreateNoteButton_clicked();

    void MenuOpenCategory();

    void MenuEditCategory();

    void MenuDeleteCategory();

private:
    Ui::Category *ui;

};

#endif // CATEGORY_H
