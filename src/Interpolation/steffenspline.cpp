#include "steffenspline.h"

#include <iostream>
#include <cmath>


//std::cout<<"Here"<<std::endl;

SteffenSpline::SteffenSpline() {}

SteffenSpline::SteffenSpline(Eigen::ArrayXd dataX, Eigen::ArrayXXd data) :
    Interp(dataX, data)
{
    this->aa = Eigen::ArrayXXd(this->lenN-1, this->lenM);
    this->bb = Eigen::ArrayXXd(this->lenN-1, this->lenM);
    this->cc = Eigen::ArrayXXd(this->lenN-1, this->lenM);
    this->dd = Eigen::ArrayXXd(this->lenN-1, this->lenM);
    this->yl = Eigen::ArrayXXd(this->lenN, this->lenM);
    this->pp = Eigen::ArrayXXd(this->lenN, this->lenM);
    
    this->getPP();
}

SteffenSpline::~SteffenSpline() {}

Eigen::ArrayXd SteffenSpline::F(double inputX)
{
    //Get the interval of inputX
    Eigen::Index curInd = this->FindIntervalInd(inputX);
    
    //x - xi
    double tempDx = inputX  - this->dataX(curInd);
    
    //Return a M size vector
    return  this->aa.row(curInd) * pow(tempDx, 3) + this->bb.row(curInd) * pow(tempDx, 2)
        + this->cc.row(curInd) * tempDx + this->dd.row(curInd);
}

void SteffenSpline::getPP()
{
    Eigen::ArrayXXd PP2;
    
    this->pp << PP1, PP2, PPN;
}