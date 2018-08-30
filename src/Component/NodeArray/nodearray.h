#ifndef NODEARRAY_H
#define NODEARRAY_H

#include <vector>

#include <Dense>
#include "node3d.h"
#include "noderow.h"
#include "emptyobject.h"
#include "element.h"
#include "elementrow.h"
#include "elementarray.h"

class NodeArray : public EmptyObject
{
public:
    NodeArray();
    NodeArray(std::string label, unsigned int tag, std::vector<NodeRow> nodeRows, Eigen::ArrayXXi keyInd, bool isUniform);
    ~NodeArray();

    NodeRow getNodeCol(Eigen::ArrayXi keyIndCol, std::string label, unsigned int tag);
    NodeArray Interp(Eigen::ArrayXd newZ);
    unsigned int setTag(unsigned int tag);

    static std::vector<Node3D*> ConcatenateVectors(std::vector<Node3D*> A, std::vector<Node3D*>B);
    std::vector<Node3D*> getNodePointers();
    Eigen::ArrayX3d getNodeCoords();
    ElementArray buildEleArray();
    std::vector<NodeArray> buildWebNodeArray(Eigen::ArrayXi webInd, Eigen::Array2i rangeInd, unsigned int meshNum);
    static Eigen::Array2i getRangeInd(Eigen::ArrayXd target, Eigen::ArrayXd range);

    std::vector<NodeRow> nodeRows;
    Eigen::ArrayXXi keyInd;
    unsigned int rowNum;
    bool isUniform;

};

#endif // NODEARRAY_H
