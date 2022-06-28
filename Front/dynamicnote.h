#ifndef DYNAMICNOTE_H
#define DYNAMICNOTE_H

#include <QTextEdit>

class DynamicNote : public QTextEdit
{
    Q_OBJECT
public:
    explicit DynamicNote(QWidget *parent = 0);
    ~DynamicNote();
    static int ResID;
    int getID();


public slots:

private:
    int noteID = 0;
};

#endif // DYNAMICNOTE_H
