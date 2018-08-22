#ifndef QUAD4_H
#define QUAD4_H


#include "element.h"
#include "node.h"

class Quad4 : public Element
{
public:
    Quad4();
    Quad4(std::string label, unsigned int tag, Node *N1, Node *N2, Node *N3, Node *N4);
    ~Quad4();
};

#endif // QUAD4_H
