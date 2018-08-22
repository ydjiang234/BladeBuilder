#ifndef NODEARRAY_H
#define NODEARRAY_H

#include <vector>

#include "node.h"
#include "emptyobject.h"

class NodeArray : public EmptyObject
{
public:
    NodeArray();
    NodeArray(std::string label, unsigned int tag, std::vector<std::vector<Node*>> nodes);
    ~NodeArray();

    std::vector<std::vector<Node*>> nodes;

};

#endif // NODEARRAY_H
