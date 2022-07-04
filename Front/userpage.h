#ifndef USERPAGE_H
#define USERPAGE_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QTcpSocket>
#include "3rdparty/json.hpp"

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
    QTcpSocket* socket;

private slots:


private:
    Ui::UserPage *ui;
};

#endif // USERPAGE_H
