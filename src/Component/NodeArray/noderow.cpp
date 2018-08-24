#include "noderow.h"
#include "linesegement.h"

NodeRow::NodeRow() {}

NodeRow::NodeRow(std::string label, unsigned int tag, std::vector<Node*> nodes) :
    EmptyObject (label, tag)
{
    this->nodes = nodes;
    this->pointNum = nodes.size();
}

NodeRow::~NodeRow() {}

Eigen::ArrayX3d NodeRow::toData3D()
{
    Eigen::ArrayX3d out(this->pointNum,3);

    //iter points
    for (unsigned int i=0; i<this->pointNum; ++i) {
        //append coordinate of each point to out
        out.row(i) = this->nodes[i]->data;
    }

    return out;
}

Eigen::ArrayX2d NodeRow::toData2D()
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
    Eigen::ArrayX3d out(newLen, 3);
    Eigen::ArrayX3d data(this->pointNum, 3);
    Eigen::ArrayX2d dataZX(this->pointNum, 2);
    Eigen::ArrayX2d dataZY(this->pointNum, 2);
    //Convert nodes to data
    data = this->toData3D();
    //Get dataZX and dataZY
    dataZX.col(0) = data.col(2);
    dataZX.col(1) = data.col(0);

    dataZY.col(0) = data.col(2);
    dataZY.col(1) = data.col(1);

    return out;
}
