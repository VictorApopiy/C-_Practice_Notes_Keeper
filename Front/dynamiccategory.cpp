#include "dynamiccategory.h"

DynamicCategory::DynamicCategory(QWidget *parent) :
    QPushButton(parent)
{
    ResID++;
    categoryID = ResID;

}

DynamicCategory::~DynamicCategory()
{

}

int DynamicCategory::getID()
{
    return categoryID;
}

int DynamicCategory::ResID = 0;
