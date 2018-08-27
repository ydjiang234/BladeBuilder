#include "patternmember.h"

PatternMember::PatternMember() {}

PatternMember::PatternMember(std::string name, std::vector<std::string> matNames, Eigen::ArrayXd thicks, Eigen::ArrayXi intPs, Eigen::ArrayXd angles) :
    Member (name)
{
    this->matNames = matNames;
    this->thicks = thicks;
    this->intPs = intPs;
    this->angles = angles;
}

PatternMember::~PatternMember() {}

void PatternMember::setData(std::string name, std::vector<std::string> matNames, Eigen::ArrayXd thicks, Eigen::ArrayXi intPs, Eigen::ArrayXd angles)
{
    this->name = name;
    this->matNames = matNames;
    this->thicks = thicks;
    this->intPs = intPs;
    this->angles = angles;
}

void PatternMember::getData(std::string* name1, std::vector<std::string>* matNames1, Eigen::ArrayXd* thicks1, Eigen::ArrayXi* intPs1, Eigen::ArrayXd* angles1)
{
    *name1 = this->name;
    *matNames1 = this->matNames;
    *thicks1 = this->thicks;
    *intPs1 = this->intPs;
    *angles1 = this->angles;
}
