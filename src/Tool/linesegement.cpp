#include "linesegement.h"
#include <iostream>
LineSegement::LineSegement() {}

LineSegement::LineSegement(std::string label, Eigen::MatrixX2d data)
{
    this->label = label;
    this->data = data;
    this->pointNum = this->data.rows();
}

LineSegement::~LineSegement() {}

void LineSegement::Interp(unsigned int number)
{
   //number is the number of segements

}

std::vector<LineSegement> LineSegement::Split(Eigen::VectorXi keyInd)
{
    std::vector<LineSegement> out;
    for (unsigned int i=0; i<keyInd.rows(); i++){
        Eigen::MatrixX2d temp;
        std::string label = this->label + "-" + std::to_string(i+1);
        if (i==0) {
            temp = this->data.block(0, 0, keyInd(i)+1, 2);
            //std::cout<<"OK"<<std::endl;
        } else {
            temp = this->data.block(keyInd(i-1), 0, keyInd(i)-keyInd(i-1)+1, 2);
            //std::cout<<"OK"<<std::endl;
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

std::pair<LineSegement, Eigen::VectorXi> LineSegement::Join(std::vector<LineSegement> lineSegs, std::string label)
{
    std::pair<LineSegement, Eigen::VectorXi> out;
    Eigen::MatrixX2d newData;
    Eigen::VectorXi keyInd(lineSegs.size()-1);
    keyInd(0) = lineSegs[0].pointNum-1;
    for (int i=0; i<lineSegs.size()-1; i++){
        unsigned int tempSize = lineSegs[i+1].pointNum;
        if (i==0) {
            newData = this->CombineMatrixV(lineSegs[i].data, lineSegs[i+1].data.block(1, 0, tempSize-1, 2));
        } else {
            keyInd(i) = keyInd(i-1) + lineSegs[i].pointNum-1;
            newData = this->CombineMatrixV(newData, lineSegs[i+1].data.block(1, 0, tempSize-1, 2));
            //std::cout<<"OK"<<std::endl;
        }
    }
    out.first = LineSegement(label, newData);
    out.second = keyInd;
    //std::cout<<"OK"<<std::endl;
    return out;
}

Eigen::MatrixX2d LineSegement::CombineMatrixV(Eigen::MatrixX2d M1, Eigen::MatrixX2d M2)
{
    Eigen::MatrixX2d out(M1.rows()+M2.rows(), 2);
    out << M1,
            M2;
    return out;
}
