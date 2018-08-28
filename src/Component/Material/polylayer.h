#ifndef POLYLAYER_H
#define POLYLAYER_H

#include <vector>
#include <Dense>

#include "emptyobject.h"
#include "layerpattern.h"

class PolyLayer : public EmptyObject
{
public:
    PolyLayer();
    PolyLayer(std::string label, unsigned int tag, std::vector<LayerPattern*> layerPats, Eigen::ArrayXi patNums, Eigen::ArrayXd offsetAngles);
    ~PolyLayer();

    void Normalize(std::vector<LayerPattern*> patOrder);
    void Trim();

    std::vector<LayerPattern*> layerPats;
    Eigen::ArrayXi patNums;
    Eigen::ArrayXd offsetAngles;
    unsigned int lpNum;
};

#endif // POLYLAYER_H
