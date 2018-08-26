#ifndef STEFFENSPLINE_H
#define STEFFENSPLINE_H

#include <Dense>
#include "interp.h"

class SteffenSpline : public Interp
{
public:
    SteffenSpline();
    SteffenSpline(Eigen::ArrayXd dataX, Eigen::ArrayXXd data);
    ~SteffenSpline();
    
    Eigen::ArrayXd F(double inputX);
    
private:
    
    

    Eigen::ArrayXXd aa, bb, cc, dd; //All are (N-1) * M size
    Eigen::ArrayXXd yl, pp; //All are N * M size
    
    
};



#endif