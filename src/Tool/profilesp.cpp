#include "profilesp.h"
#include <algorithm>

ProfileSp::ProfileSp() {}

ProfileSp::ProfileSp(std::string label, Eigen::ArrayX2d data, double chordLen, Eigen::Array3d leadCoord, double twist, Eigen::ArrayXd splitLocU, Eigen::ArrayXd splitLocL) :
    Profile(label, data, chordLen, leadCoord, twist)
{
    this->UpdateData1(splitLocU, splitLocL);
}

ProfileSp::~ProfileSp() {}

void ProfileSp::UpdateData1(Eigen::ArrayXd splitLocU, Eigen::ArrayXd splitLocL)
{
    this->splitLocU = splitLocU;
    this->splitLocL = splitLocL;
    this->keyIndU = this->getKeyInd(this->lineU.data.col(0), this->splitLocU);
    this->keyIndL = this->getKeyInd(this->lineL.data.col(0), this->splitLocL);
}

std::pair<LineSegement, Eigen::ArrayXi> ProfileSp::getData(Eigen::ArrayXi meshU, Eigen::ArrayXi meshL)
{
    std::vector<LineSegement> lineSegsU, lineSegsL, lineSegs;
    std::pair<LineSegement, Eigen::ArrayXi> out;
    Eigen::ArrayX2d temp;
    //Split the lineU and lineL
    lineSegsU = this->lineU.Split(this->keyIndU);
    lineSegsL = this->lineL.Split(this->keyIndL);
    //For each sub linesegement, split according to the index
    for (unsigned int i=0; i<meshU.rows(); ++i) {
        temp = lineSegsU[i].Interp(meshU(i));
        lineSegsU[i].Update(temp);
    }
    for (unsigned int i=0; i<meshL.rows(); ++i) {
        temp = lineSegsL[i].Interp(meshL(i));
        lineSegsL[i].Update(temp.colwise().reverse()); //Important here, dont forget to reverse the data of the lower segements
    }
    //Reverse the lineSegsL
    std::reverse(lineSegsL.begin(), lineSegsL.end());
    //Combine the lineSegsU and lineSegsL
    lineSegs = lineSegsU;
    lineSegs.insert(lineSegs.end(), lineSegsL.begin(), lineSegsL.end());
    //Join the lineSegs
    out = this->Join(lineSegs, "Combined");
    //Scale raotate and transfer
    Eigen::ArrayX2d temp1 = out.first.data;
    out.first.data = temp1;
    out.first.data = this->beforeOut(temp1);
    return out;
}

Eigen::ArrayXi ProfileSp::getKeyInd(Eigen::ArrayXd data, Eigen::ArrayXd splitLoc)
{
    Eigen::Index splitNum;
    unsigned int curInd;
    double curLoc;

    splitNum = splitLoc.rows();
    Eigen::ArrayXi out(splitNum);
    //Iter
    for (unsigned int i=0; i<splitNum; ++i) {
        curLoc = splitLoc(i);
        (data - curLoc).abs().minCoeff(&curInd);
        out(i) = curInd;
    }

    return out;
}
