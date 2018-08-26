#include <iostream>
#include "linearinterp.h"

//std::cout<<"Here"<<std::endl;

LinearInterp::LinearInterp() {}

LinearInterp::LinearInterp(Eigen::ArrayXd dataX, Eigen::ArrayXXd data) :
    Interp(dataX, data)
{
    this->BB = this->data.topRows(this->lenN-1) - this->slop.colwise() * this->dataX.topRows(this->lenN-1);
}

LinearInterp::~LinearInterp() {}

Eigen::ArrayXd LinearInterp::F(double inputX)
{
    //Find the interval
    Eigen::Index curInd = this->FindIntervalInd(inputX);
    //Claculate the value
    return this->slop.row(curInd) * inputX + this->BB.row(curInd);
}