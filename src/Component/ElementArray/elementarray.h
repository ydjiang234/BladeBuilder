#ifndef ELEMENTARRAY_H
#define ELEMENTARRAY_H

#include <vector>

#include "element.h"
#include "elementrow.h"
#include "emptyobject.h"

class ElementArray : public EmptyObject
{
public:
    ElementArray();
    ElementArray(std::string label, unsigned int tag, std::vector<ElementRow*> eleRows);
    ~ElementArray();

    std::vector<ElementRow*> eleRows;
    unsigned int rowNum;

};

#endif // ELEMENTARRAY_H
