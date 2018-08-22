#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>

#include "emptyobject.h"
#include "node.h"


class Element : public EmptyObject
{
public:
    Element();
    Element(std::string label, unsigned int tag);
    ~Element();

    unsigned int nodeNum;
    std::vector<Node*> nodes;
};

#endif // ELEMENT_H
