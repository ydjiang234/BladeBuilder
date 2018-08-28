#include "elementarray.h"

ElementArray::ElementArray() {}

ElementArray::ElementArray(std::string label, unsigned int tag, std::vector<ElementRow> eleRows) :
    EmptyObject (label, tag)
{
    this->eleRows = eleRows;
    this->rowNum = eleRows.size();
}

ElementArray::~ElementArray() {}

unsigned int ElementArray::setTag(unsigned int tag)
{
    for (ElementRow curRow : this->eleRows) {
        tag = curRow.setTag(tag);
    }
    return tag;
}
