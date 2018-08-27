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
