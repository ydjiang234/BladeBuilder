#include "node.h"

Node::Node() {}
Node::Node(std::string label, unsigned int tag)
{
    this->label = label;
    this->tag = tag;
}
Node::~Node() {}
