#include "compmember.h"

CompMember::CompMember() {}

CompMember::CompMember(std::string name, double radius, std::vector<std::string> patNames, Eigen::ArrayXi patNums) :
    Member (name)
{
    this->radius = radius;
    this->patNames = patNames;
    this->patNums = patNums;
}

CompMember::~CompMember() {}

void CompMember::setData(std::string name, double radius, std::vector<std::string> patNames, Eigen::ArrayXi patNums)
{
    this->name = name;
    this->radius = radius;
    this->patNames = patNames;
    this->patNums = patNums;
}

void CompMember::getData(std::string* name1, double* radius1, std::vector<std::string>* patNames1, Eigen::ArrayXi* patNums1)
{
    *name1 = this->name;
    *radius1 = this->radius;
    *patNames1 = this->patNames;
    *patNums1 = this->patNums;
}
