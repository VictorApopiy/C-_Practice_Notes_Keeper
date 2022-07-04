#include "popupmenu.h"

PopupMenu::PopupMenu(QPushButton* button, QWidget* parent) : QMenu(parent), m_button(button)
{
}

PopupMenu::PopupMenu(QTextEdit* textedit, QWidget* parent) : QMenu(parent), m_textedit(textedit)
{
}
void PopupMenu::showEvent(QShowEvent* event)
{
    QPoint p = this->pos();
    QRect geoB = m_button->geometry();
    this->move(p.x()+geoB.width()-this->geometry().width(), p.y());
    QRect geoT = m_textedit->geometry();
    this->move(p.x()+geoT.width()-this->geometry().width(), p.y());
}
