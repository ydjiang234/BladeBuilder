#include "linesegement.h"
#include "twopointline.h"
#include <iostream>

//std::cout<<"OK"<<std::endl;

LineSegement::LineSegement() {}

LineSegement::LineSegement(std::string label, Eigen::ArrayX2d data)
{
    this->label = label;
    this->Update(data);
}

LineSegement::~LineSegement() {}

void LineSegement::Interp(unsigned int number)
{
    //number is the number of segements
    double curArcLength, step, curUpper, curLower, ratio;
    TwoPointLine vec;
    unsigned int curIntNum = 1;
    Eigen::ArrayX2d newData = Eigen::ArrayX2d::Zero(number+1, 2);
    //New data
    newData.row(0) = this->data.row(0);
    newData.row(number) = this->data.row(this->pointNum-1);
    step = this->cumArcLength(this->pointNum-2) / number;
    //Initial
    curArcLength = curIntNum * step;
    for (unsigned int i=0; i<this->pointNum-1; ++i) {
        //current interval range
        if (i==0) {
            curUpper = this->cumArcLength(i);
            curLower = 0.0;
        } else {
            curUpper = this->cumArcLength(i);
            curLower = this->cumArcLength(i-1);
        }
        vec = TwoPointLine(this->data.row(i), this->data.row(i+1));
        while ((curArcLength<=curUpper) && (curArcLength>curLower) && (curIntNum<number)) {
            ratio = (curArcLength - curLower) / vec.length;
            newData.row(curIntNum) = vec.getPoint(ratio);
            ++curIntNum;
            curArcLength += step;
        }
    }
    this->Update(newData);
}

std::vector<LineSegement> LineSegement::Split(Eigen::ArrayXi keyInd)
{
    std::vector<LineSegement> out;
    for (unsigned int i=0; i<keyInd.rows(); i++){
        Eigen::ArrayX2d temp;
        std::string label = this->label + "-" + std::to_string(i+1);
        if (i==0) {
            temp = this->data.block(0, 0, keyInd(i)+1, 2);
            //std::cout<<"OK"<<std::endl;
        } else {
            temp = this->data.block(keyInd(i-1), 0, keyInd(i)-keyInd(i-1)+1, 2);
        }
        out.push_back(LineSegement(label, temp));

        if (i==keyInd.rows()-1) {
            temp = this->data.block(keyInd(i), 0, this->pointNum-keyInd(i), 2);
        std::string label = this->label + "-" + std::to_string(i+2);
            out.push_back(LineSegement(label, temp));
        }

    }

    return out;
}

std::pair<LineSegement, Eigen::ArrayXi> LineSegement::Join(std::vector<LineSegement> lineSegs, std::string label)
{
    std::pair<LineSegement, Eigen::ArrayXi> out;
    Eigen::ArrayX2d newData;
    Eigen::ArrayXi keyInd(lineSegs.size()-1);
    keyInd(0) = lineSegs[0].pointNum-1;
    for (int i=0; i<lineSegs.size()-1; i++){
        unsigned int tempSize = lineSegs[i+1].pointNum;
        if (i==0) {
            newData = this->CombineArrayV(lineSegs[i].data, lineSegs[i+1].data.block(1, 0, tempSize-1, 2));
        } else {
            keyInd(i) = keyInd(i-1) + lineSegs[i].pointNum-1;
            newData = this->CombineArrayV(newData, lineSegs[i+1].data.block(1, 0, tempSize-1, 2));
            //std::cout<<"OK"<<std::endl;
        }
    }
    out.first = LineSegement(label, newData);
    out.second = keyInd;
    //std::cout<<"OK"<<std::endl;
    return out;
}

void LineSegement::getArcLength()
{
    unsigned int len = this->data.rows()-1;
    TwoPointLine temp;
    this->arcLength = Eigen::ArrayXd::Zero(len);
    this->cumArcLength = Eigen::ArrayXd::Zero(len);
    for (int i=0; i<len; i++) {
        temp = TwoPointLine(this->data.row(i), this->data.row(i+1));
        this->arcLength(i) = temp.length;
        if (i==0) {
            this->cumArcLength(i) = this->arcLength(i);
        } else {
            this->cumArcLength(i) = this->arcLength(i) + this->cumArcLength(i-1);
        }
    }
}

void LineSegement::Update(Eigen::ArrayX2d data)
{
    this->data = data;
    this->pointNum = this->data.rows();
    this->getArcLength();
}

Eigen::ArrayX2d LineSegement::CombineArrayV(Eigen::ArrayX2d M1, Eigen::ArrayX2d M2)
{
    Eigen::ArrayX2d out(M1.rows()+M2.rows(), 2);
    out << M1,
            M2;
    return out;
}
