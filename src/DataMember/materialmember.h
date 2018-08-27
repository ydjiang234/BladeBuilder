#ifndef MATERIALMEMBER_H
#define MATERIALMEMBER_H

#include <string>

#include <Dense>
#include "member.h"

class MaterialMember : public Member
{
public:
    MaterialMember();
    MaterialMember(std::string name, double density, Eigen::ArrayXd others);
    ~MaterialMember();

    void setData(std::string name, double density, Eigen::ArrayXd others);

    void getData(std::string *name1, double *density1, Eigen::ArrayXd *others1);

    double density;
    Eigen::ArrayXd others;
};

#endif // MATERIALMEMBER_H
