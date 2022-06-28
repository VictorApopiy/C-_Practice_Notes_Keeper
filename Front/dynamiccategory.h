#ifndef DYNAMICCATEGORY_H
#define DYNAMICCATEGORY_H

#include <QPushButton>


class DynamicCategory : public QPushButton
{
    Q_OBJECT
public:
    explicit DynamicCategory(QWidget *parent = 0);
    ~DynamicCategory();
    static int ResID;
    int getID();


public slots:

private:
    int categoryID = 0;
};

#endif // DYNAMICCATEGORY_H
