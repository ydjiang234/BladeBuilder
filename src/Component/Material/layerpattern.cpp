#include "layerpattern.h"

LayerPattern::LayerPattern() {}

LayerPattern::LayerPattern(std::string label, unsigned int tag, std::vector<Layer> layers):
    EmptyObject (label, tag)
{
    this->layers = layers;
    this->layerNum = this->layers.size();
}

LayerPattern::~LayerPattern(){}
