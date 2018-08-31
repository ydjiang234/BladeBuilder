#include <iostream>
#include "nodearray.h"
#include "linesegement.h"


NodeArray::NodeArray() {}

NodeArray::NodeArray(std::string label, unsigned int tag, std::vector<NodeRow> nodeRows, Eigen::ArrayXXi keyInd, bool isUniform) :
    EmptyObject(label, tag)
{
    this->nodeRows = nodeRows;
    this->keyInd = keyInd;
    this->isUniform = isUniform;
    this->rowNum = nodeRows.size();
}

NodeArray::~NodeArray() {}

NodeRow NodeArray::getNodeCol(Eigen::ArrayXi keyColInd, std::string label, unsigned int tag)
{
    if (this->rowNum!=keyColInd.rows()) {
        std::cout<<"keyColInd size is not correct!"<<std::endl;
    } else {
        Node3D* curNode;
        std::vector<Node3D*> nodes;
        //Iter rom bottom to top
        for (unsigned int i=0; i<this->rowNum; ++i) {
            //For each row, get the node from the key index
            curNode = this->nodeRows[i].nodes[keyColInd(i)];
            nodes.push_back(curNode);
        }
    return NodeRow("temp", 0, nodes);
    }
}

NodeArray NodeArray::Interp(Eigen::ArrayXd newZ)
{
    if (this->isUniform) {
        Eigen::Index pointNum = this->nodeRows[0].pointNum;
        //for each node on the profile, generate the vertical noderow
        //and for the vertical noderow, interpolation according to newZ
        std::vector<Eigen::ArrayX3d> dataXYZList;
        for (Eigen::Index i=0; i<pointNum; ++i) {
            dataXYZList.push_back(this->getNodeCol(Eigen::ArrayXi::Constant(this->rowNum, 1, i), this->label, this->tag).InterpSteffen(newZ));
        }
        //For each level of newZ, get the data of a profile
        Eigen::Index levelNum = newZ.rows();
        std::vector<NodeRow> newNodeRows;
        std::vector<Node3D*> tempNodeList;
        Node3D* tempNode;
        for (Eigen::Index i=0; i<levelNum; ++i) {
            tempNodeList.clear();
            //Get each data on vNodeRow build a nodeRow
            for (Eigen::Index j=0; j<pointNum; ++j) {
                tempNode = new Node3D(this->label, this->tag, dataXYZList[j](i,0), dataXYZList[j](i,1), dataXYZList[j](i,2));
                tempNodeList.push_back(tempNode);
            }
            newNodeRows.push_back(NodeRow(this->label, this->tag, tempNodeList));
        }
        Eigen::ArrayXXi newKeyInd = (this->keyInd.row(0).matrix().transpose() * Eigen::MatrixXi::Ones(1, levelNum)).array();
        return NodeArray(this->label, this->tag, newNodeRows, newKeyInd.transpose(), true);
    }
}

unsigned int NodeArray::setTag(unsigned int tag)
{
    for (NodeRow curRow : this->nodeRows) {
        tag = curRow.setTag(tag);
    }
    return tag;
}

std::vector<Node3D*> NodeArray::getNodePointers()
{
    std::vector<Node3D*> out;
    for (NodeRow curRow : this->nodeRows) {
        out = this->ConcatenateVectors(out, curRow.nodes);
    }
    return out;
}

std::vector<Node3D*> NodeArray::getWebNodePointers()
{
    std::vector<Node3D*> out;
    for (unsigned int i=1; i<this->rowNum-1; ++i) {
        out = this->ConcatenateVectors(out, this->nodeRows[i].nodes);
    }
    return out;
}

std::vector<Node3D*> NodeArray::ConcatenateVectors(std::vector<Node3D*> A, std::vector<Node3D*>B)
{
    std::vector<Node3D*> out;
    out.reserve(A.size()+B.size());
    out.insert(out.end(), A.begin(), A.end());
    out.insert(out.end(), B.begin(), B.end());
    return out;
}

Eigen::ArrayX3d NodeArray::getNodeCoords()
{
    Eigen::ArrayX3d out;
    for (unsigned int i=0; i<this->rowNum; ++i) {
        if (i==0) {
            out = this->nodeRows[i].toDataXYZ();
        } else {
            out = LineSegement::CombineArrayV(out, this->nodeRows[i].toDataXYZ());
        }
    }
    return out;
}

ElementArray NodeArray::buildEleArray()
{
    std::vector<ElementRow> tempEleRows;
    //Iter along the nodeRows
    for (unsigned int i=0; i<this->rowNum-1; ++i) {
        tempEleRows.push_back(NodeRow::generateEleRow(this->nodeRows[i], this->nodeRows[i+1], true));
    }
    return ElementArray(this->label, this->tag, tempEleRows);
}

Eigen::Array2i NodeArray::getRangeInd(Eigen::ArrayXd target, Eigen::ArrayXd range)
{
    Eigen::Array2i out;
    Eigen::Index startInd, endInd;

    (target - range(0)).abs().minCoeff(&startInd);
    (target - range(1)).abs().minCoeff(&endInd);

    out(0) = startInd;
    out(1) = endInd;
    return out;
}

std::vector<NodeArray> NodeArray::buildWebNodeArray(Eigen::ArrayXi webInd, Eigen::Array2i rangeInd, unsigned int meshNum)
{
    std::vector<NodeArray> out;
    for (unsigned int i=0; i<webInd.rows(); ++i)
    {
        //For each webind, build a Node array
        std::vector<NodeRow> tempNodeRows;
        NodeRow curRow1 = this->getNodeCol(this->keyInd.col(webInd(i)), this->label, this->tag).getSub(rangeInd(0), rangeInd(1));
        NodeRow curRow2 = this->getNodeCol(this->keyInd.col(this->keyInd.cols()-1-webInd(i)), this->label, this->tag).getSub(rangeInd(0), rangeInd(1));
        NodeArray tempNodeArray("Web-", i, NodeRow::generateQuadNodeArray(curRow1, curRow2, meshNum), Eigen::ArrayXXi::Zero(curRow1.pointNum,1), true);
        out.push_back(tempNodeArray);
    }
    return out;
}
