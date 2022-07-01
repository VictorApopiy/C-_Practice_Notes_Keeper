#ifndef USERPAGE_H
#define USERPAGE_H

#include <QMainWindow>
#include <QScopedPointer>


namespace Ui {
class UserPage;
}

class UserPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserPage(QWidget *parent = nullptr);
    const Ui::UserPage &getUserPage() {return *ui;}
    ~UserPage();

private slots:


private:
    Ui::UserPage *ui;
};

#endif // USERPAGE_H
