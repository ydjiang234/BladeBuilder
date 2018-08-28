#include "polylayer.h"

PolyLayer::PolyLayer() {}

PolyLayer::PolyLayer(std::string label, unsigned int tag, std::vector<LayerPattern*> layerPats, Eigen::ArrayXi patNums, Eigen::ArrayXd offsetAngles) :
    EmptyObject (label, tag)
{
    this->layerPats = layerPats;
    this->lpNum = this->layerPats.size();
    this->patNums = patNums;
    this->offsetAngles = offsetAngles;
}

PolyLayer::~PolyLayer() {}
