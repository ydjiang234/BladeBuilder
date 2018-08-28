#include "elementrow.h"

ElementRow::ElementRow() {}

ElementRow::ElementRow(std::string label, unsigned int tag, std::vector<Element*> elements) :
    EmptyObject (label, tag)
{
    this->elements = elements;
}

ElementRow::~ElementRow() {}

unsigned int ElementRow::setTag(unsigned int tag)
{
    for (Element* curEle : this->elements) {
        curEle->reTag(tag);
        tag += 1;
    }
    return tag;
}
