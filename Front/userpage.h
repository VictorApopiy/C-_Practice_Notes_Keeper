#ifndef USERPAGE_H
#define USERPAGE_H

#include <QMainWindow>

namespace Ui {
class UserPage;
}

class UserPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserPage(QWidget *parent = nullptr);
    ~UserPage();

private slots:
    void on_UPLogOutButton_clicked();

private:
    Ui::UserPage *ui;
};

#endif // USERPAGE_H
