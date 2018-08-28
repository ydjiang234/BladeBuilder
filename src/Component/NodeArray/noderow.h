#ifndef NODEROW_H
#define NODEROW_H

#include <vector>

#include <Dense>
#include "node3d.h"
#include "elementrow.h"
#include "element.h"
#include "elementarray.h"
#include "quad4.h"

class NodeRow : EmptyObject
{
public:
    NodeRow();
    NodeRow(std::string label, unsigned int tag, std::vector<Node3D*> nodes);
    ~NodeRow();

    Eigen::ArrayX3d toDataXYZ();
    Eigen::ArrayX2d toDataXY();

    Eigen::ArrayX3d InterpLinear(Eigen::ArrayXd newZ);
    Eigen::ArrayX3d InterpSteffen(Eigen::ArrayXd newZ);

    unsigned int setTag(unsigned int tag);
    static ElementRow generateEleRow(NodeRow A, NodeRow B, bool isClose=true);


    std::vector<Node3D*> nodes;
    unsigned int pointNum;
};

#endif // NODEROW_H
