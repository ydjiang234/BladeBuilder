#ifndef LINEARINTERP_H
#define LINEARINTERP_H

#include <Dense>
#include "interp.h"


class LinearInterp : public Interp
{
public:
    LinearInterp();
    LinearInterp(Eigen::ArrayXd dataX, Eigen::ArrayXXd data);
    ~LinearInterp();
    
    Eigen::ArrayXXd Inter(Eigen::ArrayXd XX);
    
    Eigen::ArrayXXd BB; // Y = slop * X + BB
    //BB is a (N-1) * M size array
};

#endif // LINEARINTERP_H