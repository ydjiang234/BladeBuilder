#include "layer.h"

Layer::Layer() {}

Layer::Layer(std::string label, unsigned int tag, Material* mat, double thickness, double angle, unsigned int intNum) :
    EmptyObject (label, tag)
{
    this->mat = mat;
    this->thickness = thickness;
    this->angle = angle;
    this->intNum = intNum;
}

Layer::~Layer() {}
