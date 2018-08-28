#include "regionlayup.h"

RegionLayup::RegionLayup() {}

RegionLayup::RegionLayup(std::string label, unsigned int tag, Eigen::ArrayXd levels, std::vector<PolyLayer> polyLayers, std::vector<LayerPattern> patOrder) :
    EmptyObject (label, tag)
{
    this->levels = levels;
    this->levelNum = levels.rows();
    this->polyLayers = this->polyLayers;
    this->patOrder = patOrder;
    this->levelNum = levels.rows();
    this->polyLayers = this->polyLayers;
    this->patOrder = patOrder;
}

RegionLayup::~RegionLayup() {}
