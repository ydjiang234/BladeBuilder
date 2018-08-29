#include "layerpattern.h"

LayerPattern::LayerPattern() {}

LayerPattern::LayerPattern(std::string label, unsigned int tag, std::vector<Material*> mats, Eigen::ArrayXd thicks, Eigen::ArrayXd angles, Eigen::ArrayXi intPs):
    EmptyObject (label, tag)
{
    this->mats = mats;
    this->thicks = thicks;
    this->angles = angles;
    this->intPs = intPs;
    this->layerNum = thicks.rows();
}

LayerPattern::~LayerPattern(){}
