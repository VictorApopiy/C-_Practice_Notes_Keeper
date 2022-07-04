#include "popupmenubutton.h"

PopupMenuButton::PopupMenuButton(QPushButton* button, QWidget* parent) : QMenu(parent), m_button(button)
{
}

void PopupMenuButton::showEvent(QShowEvent* event)
{
    QPoint p = this->pos();
    QRect geoB = m_button->geometry();
    this->move(p.x()+geoB.width()-this->geometry().width(), p.y());
}
