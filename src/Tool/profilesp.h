#ifndef PROFILESP_H
#define PROFILESP_H

#include <Dense>
#include <string>
#include <vector>
#include <utility>

#include "linesegement.h"
#include "profile.h"

class ProfileSp : public Profile
{
public:
    ProfileSp();
    ProfileSp(std::string label, Eigen::ArrayX2d data, double chordLen, Eigen::Array3d leadCoord, double twist, Eigen::ArrayXd splitLocU, Eigen::ArrayXd splitLocL);
    ~ProfileSp();

    void UpdateData1(Eigen::ArrayXd splitLocU, Eigen::ArrayXd splitLocL);

    std::pair<LineSegement, Eigen::ArrayXi> getData(Eigen::ArrayXi meshU, Eigen::ArrayXi meshL);

    Eigen::ArrayXd splitLocU, splitLocL;
    Eigen::ArrayXi keyIndU, keyIndL;

private:
    Eigen::ArrayXi getKeyInd(Eigen::ArrayXd data, Eigen::ArrayXd splitLoc);

};

#endif // PROFILESP_H
