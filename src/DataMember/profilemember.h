#ifndef PROFILEMEMBER_H
#define PROFILEMEMBER_H

#include <string>

#include <Dense>
#include "member.h"

class ProfileMember : public Member
{
public:
    ProfileMember();
    ProfileMember(std::string name, Eigen::ArrayXd pros, Eigen::ArrayXd splitLocU, Eigen::ArrayXd splitLocL, Eigen::ArrayXd dataX, Eigen::ArrayXd dataY);
    ~ProfileMember();

    void setData(std::string name, Eigen::ArrayXd pros, Eigen::ArrayXd splitLocU, Eigen::ArrayXd splitLocL, Eigen::ArrayXd dataX, Eigen::ArrayXd dataY);
    void getData(std::string* name1, Eigen::ArrayXd* pros1, Eigen::ArrayXd* splitLocU1, Eigen::ArrayXd* splitLocL1, Eigen::ArrayXd* dataX1, Eigen::ArrayXd* dataY1);

    Eigen::ArrayXd pros, splitLocU, splitLocL, dataX, dataY;
};

#endif // PROFILEMEMBER_H
