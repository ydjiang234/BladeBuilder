#include "twopointline.h"
#include <math.h>

TwoPointLine::TwoPointLine() {}
TwoPointLine::TwoPointLine(Eigen::Array2d P1, Eigen::Array2d P2)
{
    this->P1 = P1;
    this->P2 = P2;
    this->length = this->getLength(this->P1, this->P2);
}

TwoPointLine::~TwoPointLine() {}

Eigen::Array2d TwoPointLine::getPoint(double ratio)//0<=ratio<=1
{
    Eigen::Array2d out;
    double dx, dy;
    dx = this->P2(0) - this->P1(0);
    dy = this->P2(1) - this->P1(1);

    out << this->P1(0) + dx * ratio, this->P1(1) + dy * ratio;

    return out;
}

double TwoPointLine::getLength(Eigen::Array2d P1, Eigen::Array2d P2)
{
    double out;
    Eigen::Array2d vec;
    vec = P1 - P2;
    out = sqrt(vec.pow(2).sum());
    return out;
}
