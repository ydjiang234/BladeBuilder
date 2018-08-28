#ifndef LAYER_H
#define LAYER_H


#include <vector>

#include "emptyobject.h"
#include "material.h"

class Layer : public EmptyObject
{
public:
    Layer();
    Layer(std::string label, unsigned int tag, Material* mat, double thickness, double angle, unsigned int intNum);
    ~Layer();

    Material* mat;
    double thickness, angle;
    unsigned int intNum;
};

#endif // LAYER_H
