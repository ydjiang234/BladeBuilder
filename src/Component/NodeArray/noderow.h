#ifndef NODEROW_H
#define NODEROW_H

#include <vector>

#include <Dense>
#include "node.h"


class NodeRow : EmptyObject
{
public:
    NodeRow();
    NodeRow(std::string label, unsigned int tag, std::vector<Node*> nodes);
    ~NodeRow();

    Eigen::ArrayX3d toDataXYZ();
    Eigen::ArrayX2d toDataXY();

    Eigen::ArrayX3d InterpLinear(Eigen::ArrayXd newZ);


    std::vector<Node*> nodes;
    unsigned int pointNum;
};

#endif // NODEROW_H
