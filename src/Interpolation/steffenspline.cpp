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
    Eigen::ArrayXXd PP2, si1, si;
    Eigen::ArrayXd PP1, PPN, s1, s2, sn1, sn, hi1, hi;
    double h1, h2, hn1, hn, part1, partn;
    s1 = this->slop.row(0);
    s2 = this->slop.row(1);
    sn1 = this->slop.row(this->lenN-3);
    sn = this->slop.row(this->lenN-2);
    h1 = this->dX(0);
    h2 = this->dX(1);
    hn1 = this->dX(this->lenN-3);
    hn = this->dX(this->lenN-2);
    part1 = h1 / (h1 + h2);
    partn = hn1 / (hn1 + hn);
    
    si1 = this->slop.topRows(this->lenN-2);
    si = this->slop.bottomRows(this->lenN-2);
    hi1 = this->dX.topRows(this->lenN-2);
    hi = this->dX.bottomRows(this->lenN-2);
    
    PP1 = s1 * (1 + part1) - s2 * part1;
    
    PPN = sn * (1 + partn) - sn1 * partn;
    
    PP2 = (si1.colwise() * hi + si.colwise() * hi1).colwise() / (hi1 + hi);
    
    this->pp.row(0) = PP1;
    
    this->pp.row(this->lenN-1) = PPN;
    std::cout<<"Here"<<std::endl;
}