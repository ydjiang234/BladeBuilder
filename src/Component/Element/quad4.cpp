#include "quad4.h"

Quad4::Quad4() {}
Quad4::Quad4(std::string label, unsigned int tag, Node *N1, Node *N2, Node *N3, Node *N4):
    Element (label, tag)
{
    this->nodes.push_back(N1);
    this->nodes.push_back(N2);
    this->nodes.push_back(N3);
    this->nodes.push_back(N4);
    this->nodeNum = 4;
}
Quad4::~Quad4() {}
