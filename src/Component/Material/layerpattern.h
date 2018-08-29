#ifndef LAYERPATTERN_H
#define LAYERPATTERN_H

#include <vector>

#include <Dense>
#include "emptyobject.h"
#include "material.h"

class LayerPattern : public EmptyObject
{
public:
    LayerPattern();
    LayerPattern(std::string label, unsigned int tag, std::vector<Material*> mats, Eigen::ArrayXd thicks, Eigen::ArrayXd angles, Eigen::ArrayXi intPs);
    ~LayerPattern();

    std::vector<Material*> mats;
    Eigen::ArrayXd thicks, angles;
    Eigen::ArrayXi intPs;
    unsigned int layerNum;
};

#endif // LAYERPATTERN_H
