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

    Eigen::ArrayX3d toData3D();
    Eigen::ArrayX2d toData2D();

    Eigen::ArrayX3d InterpLinear(Eigen::ArrayXd newZ);


    std::vector<Node*> nodes;
    unsigned int pointNum;
};

#endif // NODEROW_H
