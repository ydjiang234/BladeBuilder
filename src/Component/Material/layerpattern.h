#ifndef LAYERPATTERN_H
#define LAYERPATTERN_H

#include <vector>

#include "emptyobject.h"
#include "layer.h"

class LayerPattern : EmptyObject
{
public:
    LayerPattern();
    LayerPattern(std::string label, unsigned int tag, std::vector<Layer*> layers);
    ~LayerPattern();

    std::vector<Layer*> layers;
    unsigned int layerNum;
};

#endif // LAYERPATTERN_H
