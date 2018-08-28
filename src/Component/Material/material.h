#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>

#include <Dense>
#include "emptyobject.h"

class Material : public EmptyObject
{
public:
    Material();
    Material(std::string label, unsigned int tag, double density, Eigen::ArrayXd others);
    ~Material();

    double density;
    Eigen::ArrayXd others;
};

#endif // MATERIAL_H
