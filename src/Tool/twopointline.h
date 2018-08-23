#ifndef TWOPOINTLINE_H
#define TWOPOINTLINE_H

#include <Dense>

class TwoPointLine
{
public:
    TwoPointLine();
    TwoPointLine(Eigen::Array2d P1, Eigen::Array2d P2);
    ~TwoPointLine();

    Eigen::Array2d getPoint(double ratio);//0<=ratio<=1
    double getLength(Eigen::Array2d P1, Eigen::Array2d P2);

    Eigen::Array2d P1, P2;
    double length, angle;
};

#endif // TWOPOINTLINE_H
