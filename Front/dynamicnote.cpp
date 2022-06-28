#include "dynamicnote.h"

DynamicNote::DynamicNote(QWidget *parent) :
    QTextEdit(parent)
{
    ResID++;
    noteID = ResID;

}

DynamicNote::~DynamicNote()
{

}

int DynamicNote::getID()
{
    return noteID;
}

int DynamicNote::ResID = 0;
