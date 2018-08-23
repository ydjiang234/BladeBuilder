#include "profile.h"
#include <cmath>

Profile::Profile() {}

Profile::Profile(std::string label, Eigen::ArrayX2d data, double chordLen, Eigen::Array3d leadCoord, double twist) :
    LineSegement (label, data)
{
    this->UpdateData(data, chordLen, leadCoord, twist);
}

Profile::~Profile() {}

void Profile::UpdateData(Eigen::ArrayX2d data, double chordLen, Eigen::Array3d leadCoord, double twist)
{
    this->Update(data);
    this->chordLen = chordLen;
    this->leadCoord = leadCoord;
    this->twist = twist;
}

Eigen::ArrayX2d Profile::Rotate(Eigen::ArrayX2d data, double angle)
{
    Eigen::Index len = data.rows();
    Eigen::ArrayXd tempX, tempY;
    Eigen::ArrayX2d out(len, 2);

    tempX = data.col(0);
    tempY = data.col(1);

    out.col(0) = tempX * cos(angle) - tempY * sin(angle);
    out.col(1) = tempX * sin(angle) + tempY * cos(angle);

    return out;
}

Eigen::ArrayX2d Profile::Scale(Eigen::ArrayX2d data, double factor)
{
    Eigen::Index len = data.rows();
    Eigen::ArrayX2d out(len, 2);

    out = data * factor;

    return out;
}

Eigen::ArrayX2d Profile::Transfer(Eigen::ArrayX2d data, Eigen::Array2d vec)
{
    Eigen::Index len = data.rows();
    Eigen::ArrayX2d out(len, 2);

    out.col(0) = data.col(0) + vec(0);
    out.col(1) = data.col(1) + vec(1);

    return out;
}
