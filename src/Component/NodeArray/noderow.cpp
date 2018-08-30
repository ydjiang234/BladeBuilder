#include "noderow.h"
#include "linesegement.h"
#include "steffenspline.h"
#include "linearinterp.h"

//std::cout<<"Here"<<std::endl;

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

NodeRow NodeRow::getSub(unsigned int startInd, unsigned int endInd)
{
    std::vector<Node3D*> newNodes(&this->nodes[startInd], &this->nodes[endInd]);
    return NodeRow(this->label, this->tag, newNodes);
}

std::vector<NodeRow> NodeRow::generateQuadNodeArray(NodeRow A, NodeRow B, unsigned int meshNum)
{
    unsigned int nodeNum = A.pointNum;
    Eigen::Array2d oldT;
    oldT<<0, 1;
    Eigen::ArrayXd newT = Eigen::ArrayXd::LinSpaced(meshNum+1, 0, 1);
    Eigen::ArrayXXd tempAxyz = A.toDataXYZ();
    Eigen::ArrayXXd tempBxyz = B.toDataXYZ();

    Eigen::Array2Xd tempX(2, nodeNum);
    tempX.row(0) = tempAxyz.col(0).transpose();
    tempX.row(1) = tempBxyz.col(0).transpose();
    LinearInterp tempInterpX(oldT, tempX);
    Eigen::ArrayXXd newX = tempInterpX.Inter(newT).topRows(meshNum).bottomRows(meshNum-1);

    Eigen::Array2Xd tempY(2, nodeNum);
    tempY.row(0) = tempAxyz.col(1).transpose();
    tempY.row(1) = tempBxyz.col(1).transpose();
    LinearInterp tempInterpY(oldT, tempY);
    Eigen::ArrayXXd newY = tempInterpY.Inter(newT).topRows(meshNum).bottomRows(meshNum-1);

    Eigen::Array2Xd tempZ(2, nodeNum);
    tempZ.row(0) = tempAxyz.col(2).transpose();
    tempZ.row(1) = tempBxyz.col(2).transpose();
    LinearInterp tempInterpZ(oldT, tempZ);
    Eigen::ArrayXXd newZ = tempInterpZ.Inter(newT).topRows(meshNum).bottomRows(meshNum-1);

    std::vector<NodeRow> out;
    out.push_back(A);

    Node3D* curNode;
    std::vector<Node3D*> tempNodeList;
    for (Eigen::Index i=0; i<meshNum-1; ++i) {
        tempNodeList.clear();
        for (Eigen::Index j=0; j<nodeNum; ++j) {
            curNode = new Node3D("test", 0, newX(i, j), newY(i, j), newZ(i, j));
            tempNodeList.push_back(curNode);
        }
        out.push_back(NodeRow("test", i, tempNodeList));
    }

    out.push_back(B);
    return out;
}
