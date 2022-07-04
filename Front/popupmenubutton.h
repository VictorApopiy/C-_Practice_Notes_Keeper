#ifndef POPUPMENUBUTTON_H
#define POPUPMENUBUTTON_H

#include <QMenu>
#include <QPushButton>
#include <QObject>

class QPushButton;
class QWidget;

class PopupMenuButton : public QMenu
{
    Q_OBJECT
public:
    explicit PopupMenuButton(QPushButton* button, QWidget* parent = 0);
    void showEvent(QShowEvent* event);
private:
    QPushButton* m_button;
};

#endif // POPUPMENUBUTTON_H
