#ifndef POPUPMENUTEXTEDIT_H
#define POPUPMENUTEXTEDIT_H

#include <QMenu>
#include <QPushButton>
#include <QObject>

class QTextEdit;
class QWidget;

class PopupMenuTextEdit : public QMenu
{
    Q_OBJECT
public:
    explicit PopupMenuTextEdit(QTextEdit* textedit, QWidget* parent = 0);
    void showEvent(QShowEvent* event);
private:
    QTextEdit* m_textedit;
};
#endif // POPUPMENUTEXTEDIT_H
