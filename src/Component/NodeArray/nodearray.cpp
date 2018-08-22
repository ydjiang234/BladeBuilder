#include "nodearray.h"

NodeArray::NodeArray() {}

NodeArray::NodeArray(std::string label, unsigned int tag, std::vector<std::vector<Node*>> nodes) :
    EmptyObject (label, tag)
{
    this->nodes = nodes;
}

NodeArray::~NodeArray() {}
