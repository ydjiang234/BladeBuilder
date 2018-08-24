#ifndef NODEARRAY_H
#define NODEARRAY_H

#include <vector>

#include <Dense>
#include "node.h"
#include "noderow.h"
#include "emptyobject.h"

class NodeArray : public EmptyObject
{
public:
    NodeArray();
    NodeArray(std::string label, unsigned int tag, std::vector<NodeRow> nodeRows);
    ~NodeArray();

    NodeRow getNodeCol(Eigen::ArrayXi keyIndCol, std::string label, unsigned int tag);

    std::vector<NodeRow> nodeRows;
    unsigned int rowNum;


};

#endif // NODEARRAY_H
