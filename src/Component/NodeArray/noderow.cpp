#include "noderow.h"

NodeRow::NodeRow() {}

NodeRow::NodeRow(std::string label, unsigned int tag, std::vector<Node*> nodes) :
    EmptyObject (label, tag)
{
    this->nodes = nodes;
}

NodeRow::~NodeRow() {}
