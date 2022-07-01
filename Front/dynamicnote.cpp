#include "dynamicnote.h"

DynamicNote::DynamicNote(QWidget *parent) :
    QTextEdit(parent)
{
    ResID++;
    m_noteID = ResID;

}

DynamicNote::~DynamicNote()
{

}

int DynamicNote::getID()
{
    return m_noteID;
}

int DynamicNote::ResID = 0;
