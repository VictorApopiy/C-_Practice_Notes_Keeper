#include "popupmenutextedit.h"

PopupMenuTextEdit::PopupMenuTextEdit(QTextEdit* textedit, QWidget* parent) : QMenu(parent), m_textedit(textedit)
{
}

void PopupMenuTextEdit::showEvent(QShowEvent* event)
{
    QPoint p = this->pos();
    this->move(p.x()-this->geometry().width(), p.y());
}
