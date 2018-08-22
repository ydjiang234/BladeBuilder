#ifndef ELEMENTROW_H
#define ELEMENTROW_H

#include <vector>

#include "emptyobject.h"
#include "element.h"


class ElementRow : public EmptyObject
{
public:
    ElementRow();
    ElementRow(std::string label, unsigned int tag, std::vector<Element> elements);
};

#endif // ELEMENTROW_H
