#ifndef REGISTER_H
#define REGISTER_H

#include <QMainWindow>
#include <QScopedPointer>

class Category;

namespace Ui {
class Register;
}

class Register : public QMainWindow
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:


private:
    Ui::Register *ui;
    QScopedPointer <Category> m_categoryform;
};

#endif // REGISTER_H
