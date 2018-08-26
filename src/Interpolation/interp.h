#ifndef INTERP_H
#define INTERP_H

#include <Dense>

class Interp
{
public:
    Interp();
    Interp(Eigen::ArrayXd dataX, Eigen::ArrayXXd data);
    ~Interp();

    Eigen::Index FindIntervalInd(double inputX);
    virtual Eigen::ArrayXd F(double inputX);
    Eigen::ArrayXXd Inter(Eigen::ArrayXd XX);

    Eigen::ArrayXd dataX, dX;
    //dataX is a N size vector
    //dX is a N-1 size vector
    Eigen::ArrayXXd data, slop;
    //data is a N*M size array
    //slop is a (N-1)*M size array;
    Eigen::Index lenN, lenM;
    //lenN = N, lenM = M
};

#endif // INTERP_H
