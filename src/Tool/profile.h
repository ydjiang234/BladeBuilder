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

    void UpdateData(double chordLen, Eigen::Array3d leadCoord, double twist);

    virtual Eigen::ArrayX2d getData(unsigned int meshNum);

    double chordLen, twist;
    Eigen::Array3d leadCoord;
    LineSegement lineU, lineL;
    
    Eigen::ArrayX2d Rotate(Eigen::ArrayX2d data, double angle);
    Eigen::ArrayX2d Scale(Eigen::ArrayX2d data, double factor);
    Eigen::ArrayX2d Transfer(Eigen::ArrayX2d data, Eigen::Array2d vec);

private:
    std::pair<Eigen::ArrayX2d, Eigen::ArrayX2d> SeparateUL(Eigen::ArrayX2d data);
    Eigen::ArrayX2d ReOrder(Eigen::ArrayX2d data);
    bool IsEqual(double a, double b);
};

#endif // PROFILE_H
