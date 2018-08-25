#include "linearinterp.h"

LinearInterp::LinearInterp() {}

LinearInterp::LinearInterp(Eigen::ArrayXd dataX, Eigen::ArrayXXd data) :
    Interp(dataX, data)
{
    this->BB = this->data.topRows(this->lenN-1) - this->slop.colwise() * this->dataX.topRows(this->lenN-1);
}

LinearInterp::~LinearInterp() {}

Eigen::ArrayXXd LinearInterp::Inter(Eigen::ArrayXd XX)
{
    
}