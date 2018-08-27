#ifndef PATTERNMEMBER_H
#define PATTERNMEMBER_H

#include <string>
#include <vector>

#include <Dense>
#include "member.h"

class PatternMember : public Member
{
public:
    PatternMember();
    PatternMember(std::string name, std::vector<std::string> matNames, Eigen::ArrayXd thicks, Eigen::ArrayXi intPs, Eigen::ArrayXd angles);
    ~PatternMember();

    void setData(std::string name, std::vector<std::string> matNames, Eigen::ArrayXd thicks, Eigen::ArrayXi intPs, Eigen::ArrayXd angles);
    void getData(std::string* name1, std::vector<std::string>* matNames1, Eigen::ArrayXd* thicks1, Eigen::ArrayXi* intPs1, Eigen::ArrayXd* angles1);

    std::vector<std::string> matNames;
    Eigen::ArrayXd thicks, angles;
    Eigen::ArrayXi intPs;
};

#endif // PATTERNMEMBER_H
