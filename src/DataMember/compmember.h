#ifndef COMPMEMBER_H
#define COMPMEMBER_H

#include <string>
#include <vector>

#include <Dense>
#include "member.h"

class CompMember : public Member
{
public:
    CompMember();
    CompMember(std::string name, double radius, std::vector<std::string> patNames, Eigen::ArrayXi patNums);
    ~CompMember();

    void setData(std::string name, double radius, std::vector<std::string> patNames, Eigen::ArrayXi patNums);
    void getData(std::string* name1, double* radius1, std::vector<std::string>* patNames1, Eigen::ArrayXi* patNums1);

    double radius;
    std::vector<std::string> patNames;
    Eigen::ArrayXi patNums;
};

#endif // COMPMEMBER_H
