#ifndef NODEROW_H
#define NODEROW_H

#include <vector>
#include "node.h"


class NodeRow : EmptyObject
{
public:
    NodeRow();
    NodeRow(std::string label, unsigned int tag, std::vector<Node*> nodes);
    ~NodeRow();


    std::vector<Node*> nodes;
};

#endif // NODEROW_H
