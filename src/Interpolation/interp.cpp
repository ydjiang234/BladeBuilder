#include "interp.h"
#include <iostream>

//std::cout<<"Here"<<std::endl;

Interp::Interp() {}

Interp::Interp(Eigen::ArrayXd dataX, Eigen::ArrayXXd data)
{
    unsigned int len1, len2;
    len1 = dataX.rows();
    len2 = data.rows();
    if (len1!=len2) {
        std::cout<<"The size of input arrays are not equal!"<<std::endl;
    } else {
        this->dataX = dataX;
        this->data = data;
        this->lenN = len1;
        this->lenM = data.cols();
        //
        this->dX = this->dataX.tail(this->lenN-1) - this->dataX.head(this->lenN-1);
        this->slop = (this->data.bottomRows(this->lenN-1) - this->data.topRows(this->lenN-1)).colwise()
                / this->dX;
    }
}

Interp::~Interp() {}

Eigen::Index Interp::FindIntervalInd(double inputX)
{
    Eigen::Index curInd;

    //Find the closest ind
    if (inputX > this->dataX(this->lenN-1)) {
        //curInd is beyond right side
        curInd = this->lenN-1;
    } else if (inputX < this->dataX(0)) {
        //curInd is beyond left side
        curInd = -1;
    } else if (inputX == this->dataX(this->lenN-1)) {
        //the last point
        curInd = this->lenN-2;
    } else {
        //Within the X range
        (this->dataX - inputX).abs().minCoeff(&curInd);
        //Check which side is closer
        if (this->dataX(curInd) > inputX) {
            curInd -= 1;
        }
    }
    return curInd;
}


Eigen::ArrayXXd Interp::Inter(Eigen::ArrayXd XX)
{
    Eigen::ArrayXXd out;
    return out;
}
