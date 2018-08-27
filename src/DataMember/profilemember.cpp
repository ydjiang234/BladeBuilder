#include "profilemember.h"

ProfileMember::ProfileMember() {}

ProfileMember::ProfileMember(std::string name, Eigen::ArrayXd pros, Eigen::ArrayXd splitLocU, Eigen::ArrayXd splitLocL, Eigen::ArrayXd dataX, Eigen::ArrayXd dataY) :
    Member(name)
{
    this->pros = pros;
    this->splitLocU = splitLocU;
    this->splitLocL = splitLocL;
    this->dataX = dataX;
    this->dataY = dataY;
}

ProfileMember::~ProfileMember() {}

void ProfileMember::setData(std::string name, Eigen::ArrayXd pros, Eigen::ArrayXd splitLocU, Eigen::ArrayXd splitLocL, Eigen::ArrayXd dataX, Eigen::ArrayXd dataY)
{
    this->name = name;
    this->pros = pros;
    this->splitLocU = splitLocU;
    this->splitLocL = splitLocL;
    this->dataX = dataX;
    this->dataY = dataY;
}

void ProfileMember::getData(std::string* name1, Eigen::ArrayXd* pros1, Eigen::ArrayXd* splitLocU1, Eigen::ArrayXd* splitLocL1, Eigen::ArrayXd* dataX1, Eigen::ArrayXd* dataY1)
{
    *name1 = this->name;
    *pros1 = this->pros;
    *splitLocU1 = this->splitLocU;
    *splitLocL1 = this->splitLocL;
    *dataX = this->dataX;
    *dataY = this->dataY;
}
