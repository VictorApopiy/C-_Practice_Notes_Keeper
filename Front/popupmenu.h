#ifndef POPUPMENU_H
#define POPUPMENU_H

#include <QMenu>
#include <QPushButton>
#include <QTextEdit>
#include <QObject>

class QPushButton;
class QTextEdit;
class QWidget;

class PopupMenu : public QMenu
{
    Q_OBJECT
public:
    explicit PopupMenu(QPushButton* button, QWidget* parent = 0);
    explicit PopupMenu(QTextEdit* textedit, QWidget* parent = 0);
    void showEvent(QShowEvent* event);
private:
    QPushButton* m_button;
    QTextEdit* m_textedit;
};

#endif // POPUPMENU_H
