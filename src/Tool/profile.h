#ifndef PROFILE_H
#define PROFILE_H

#include <Dense>
#include <string>
#include <vector>
#include <utility>

#include "linesegement.h"

class Profile : public LineSegement
{
public:
    Profile();
    Profile(std::string label, Eigen::ArrayX2d data, double chordLen, Eigen::Array3d leadCoord, double twist);
    ~Profile();

    void UpdateData(Eigen::ArrayX2d data, double chordLen, Eigen::Array3d leadCoord, double twist);

    double chordLen;
    Eigen::Array3d leadCoord;
    double twist;

//private:
    std::pair<Eigen::ArrayX2d, Eigen::ArrayX2d> SeparateUL(Eigen::ArrayX2d data);
    Eigen::ArrayX2d Rotate(Eigen::ArrayX2d data, double angle);
    Eigen::ArrayX2d Scale(Eigen::ArrayX2d data, double factor);
    Eigen::ArrayX2d Transfer(Eigen::ArrayX2d data, Eigen::Array2d vec);
};

#endif // PROFILE_H
