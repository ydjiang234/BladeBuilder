#include "materialmember.h"

MaterialMember::MaterialMember() {}

MaterialMember::MaterialMember(std::string name, double density, Eigen::ArrayXd others) :
    Member(name)
{
    this->density = density;
    this->others = others;
}

MaterialMember::~MaterialMember() {}

void MaterialMember::setData(std::string name, double density, Eigen::ArrayXd others)
{
    this->name = name;
    this->density = density;
    this->others = others;
}

void MaterialMember::getData(std::string *name1, double *density1, Eigen::ArrayXd *others1)
{
    *name1 = this->name;
    *density1 = this->density;
    *others1 = this->others;
}
