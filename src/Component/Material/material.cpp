#include "material.h"

Material::Material() {}

Material::Material(std::string label, unsigned int tag, double density, Eigen::ArrayXd others) :
    EmptyObject (label, tag)
{
    this->density = density;
    this->others = others;
}

Material::~Material() {}
