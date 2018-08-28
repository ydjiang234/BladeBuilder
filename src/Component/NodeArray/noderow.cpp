#include "noderow.h"
#include "linesegement.h"
#include "steffenspline.h"
#include "linearinterp.h"

NodeRow::NodeRow() {}

NodeRow::NodeRow(std::string label, unsigned int tag, std::vector<Node3D*> nodes) :
    EmptyObject (label, tag)
{
    this->nodes = nodes;
    this->pointNum = nodes.size();
}

NodeRow::~NodeRow() {}

Eigen::ArrayX3d NodeRow::toDataXYZ()
{
    Eigen::ArrayX3d out(this->pointNum,3);

    //iter points
    for (unsigned int i=0; i<this->pointNum; ++i) {
        //append coordinate of each point to out
        out.row(i) = this->nodes[i]->data;
    }

    return out;
}

Eigen::ArrayX2d NodeRow::toDataXY()
{
    Eigen::ArrayX2d out(this->pointNum,2);

    //iter points
    for (unsigned int i=0; i<this->pointNum; ++i) {
        //append coordinate of each point to out
        out.row(i) = this->nodes[i]->data.head(2);
    }

    return out;
}

Eigen::ArrayX3d NodeRow::InterpLinear(Eigen::ArrayXd newZ)
{
    unsigned int newLen;
    newLen = newZ.rows();
    Eigen::ArrayX3d data1(this->pointNum, 3);
    Eigen::ArrayX3d dataNew(newLen, 3);
    //Convert nodes to data
    data1 = this->toDataXYZ();
    //Get the new data
    LinearInterp curInter(data1.col(2), data1);
    dataNew = curInter.Inter(newZ);
    
    return dataNew;
}

Eigen::ArrayX3d NodeRow::InterpSteffen(Eigen::ArrayXd newZ)
{
    unsigned int newLen;
    newLen = newZ.rows();
    Eigen::ArrayX3d data1(this->pointNum, 3);
    Eigen::ArrayX3d dataNew(newLen, 3);
    //Convert nodes to data
    data1 = this->toDataXYZ();
    //Get the new data
    SteffenSpline curInter(data1.col(2), data1);
    dataNew = curInter.Inter(newZ);

    return dataNew;
}

unsigned int NodeRow::setTag(unsigned int tag)
{
    for (Node3D* curNode : this->nodes) {
        curNode->reTag(tag);
        tag += 1;
    }
    return tag;
}

ElementRow NodeRow::generateEleRow(NodeRow A, NodeRow B, bool isClose)
{
    std::vector<Node3D*> tempA, tempB;
    tempA = A.nodes;
    tempB = B.nodes;
    if (isClose) {
        //If isclose, append the first node pointer to the end for each nodeRows
        tempA.reserve(A.pointNum+1);
        tempB.reserve(B.pointNum+1);
        tempA.insert(tempA.end(), A.nodes.begin(), A.nodes.end());
        tempA.push_back(A.nodes[0]);
        tempB.insert(tempB.end(), B.nodes.begin(), B.nodes.end());
        tempB.push_back(B.nodes[0]);
    }
    //Iter and build elements
    std::vector<Element*> tempEleList;
    for (unsigned int i=0; i<tempA.size()-1; ++i) {
        Quad4 *curEle = new Quad4(A.label, A.tag, tempA[i], tempA[i+1], tempB[i+1], tempB[i]);
        tempEleList.push_back(curEle);
    }
    //Build a new ElementRow
    return ElementRow(A.label, A.tag, tempEleList);
}
