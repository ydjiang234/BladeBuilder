#include <iostream>
#include "nodearray.h"


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
        NodeRow tempRow;
        std::vector<Eigen::ArrayX3d> tempList;
        Eigen::ArrayX3d tempData;
        for (Eigen::Index i=0; i<this->nodeRows[0].pointNum; ++i) {
            tempRow = this->getNodeCol(Eigen::ArrayXi::Ones(this->rowNum)*i, this->label, this->tag);
            tempData = tempRow.InterpSteffen(newZ);
            tempList.push_back(tempData);
        }
        //Rebuild a new NowArray
        Eigen::ArrayXXi curKeyInd(newZ.rows(), this->keyInd.cols());
        Node3D *curNode;
        std::vector<Node3D*> curNodeList;
        std::vector<NodeRow> curNodeRowList;
        for (Eigen::Index i=0; i<newZ.rows(); ++i) {
            curNodeList.clear();
            for (Eigen::Index j=0; j<this->nodeRows[0].pointNum; ++j) {
                curNode = new Node3D(this->label, this->tag, tempList[j](i,0), tempList[j](i,1), tempList[j](i,2));
                curNodeList.push_back(curNode);
            }
            tempRow = NodeRow(this->label, this->tag, curNodeList);
            curNodeRowList.push_back(tempRow);
            curKeyInd.row(i) = this->keyInd(0);
        }
        return NodeArray(this->label, this->tag, curNodeRowList, curKeyInd, true);
    }
}
