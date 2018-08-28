#ifndef REGIONLAYUP_H
#define REGIONLAYUP_H


#include <vector>
#include <Dense>

#include "emptyobject.h"
#include "polylayer.h"
#include "layerpattern.h"

class RegionLayup : public EmptyObject
{
public:
    RegionLayup();
    RegionLayup(std::string label, unsigned int tag, Eigen::ArrayXd levels, std::vector<PolyLayer> polyLayers, std::vector<LayerPattern> patOrder);
    ~RegionLayup();

    Eigen::ArrayXd levels;
    unsigned int levelNum;
    std::vector<PolyLayer> polyLayers;
    std::vector<LayerPattern> patOrder;
};

#endif // REGIONLAYUP_H
