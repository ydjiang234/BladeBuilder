#include "elementrow.h"

ElementRow::ElementRow() {}

ElementRow::ElementRow(std::string label, unsigned int tag, std::vector<Element*> elements) :
    EmptyObject (label, tag)
{
    this->elements = elements;
}

ElementRow::~ElementRow() {}
