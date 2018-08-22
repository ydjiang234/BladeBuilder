#include "emptyobject.h"

EmptyObject::EmptyObject() {}

EmptyObject::EmptyObject(std::string label, unsigned int tag)
{
    this->label = label;
    this->tag = tag;
}
