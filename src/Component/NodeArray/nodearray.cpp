#include <iostream>
#include "nodearray.h"


NodeArray::NodeArray() {}

NodeArray::NodeArray(std::string label, unsigned int tag, std::vector<NodeRow> nodeRows) :
    EmptyObject(label, tag)
{
    this->nodeRows = nodeRows;
    this->rowNum = nodeRows.size();
}

NodeArray::~NodeArray() {}

NodeRow NodeArray::getNodeCol(Eigen::ArrayXi keyColInd, std::string label, unsigned int tag)
{
    if (this->rowNum!=keyColInd.rows()) {
        std::cout<<"keyColInd size is not correct!"<<std::endl;
    } else {
        Node* curNode;
        std::vector<Node*> nodes;
        //Iter rom bottom to top
        for (unsigned int i=0; i<this->rowNum; ++i) {
            //For each row, get the node from the key index
            curNode = this->nodeRows[i].nodes[keyColInd(i)];
            nodes.push_back(curNode);
        }
    }

}
