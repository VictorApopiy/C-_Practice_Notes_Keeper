#include "dynamiccategory.h"

DynamicCategory::DynamicCategory(QWidget *parent) :
    QPushButton(parent)
{
    ResID++;
    m_categoryID = ResID;

}

DynamicCategory::~DynamicCategory()
{

}

int DynamicCategory::getID()
{
    return m_categoryID;
}

int DynamicCategory::ResID = 0;
