#include "regionlayup.h"
#include "linearinterp.h"

RegionLayup::RegionLayup() {}

RegionLayup::RegionLayup(std::string label, unsigned int tag, Eigen::ArrayXd levels, std::vector<PolyLayer> polyLayers, std::vector<LayerPattern*> patOrder) :
    EmptyObject (label, tag)
{
    this->levels = levels;
    this->levelNum = levels.rows();
    this->polyLayers = polyLayers;
    this->patOrder = patOrder;
}

RegionLayup::~RegionLayup() {}

void RegionLayup::Iterp(Eigen::ArrayXd newZ)
{
    //Normalize the PloyLayers
    Eigen::ArrayXi tempNum(this->levelNum);
    for (unsigned int i=0; i<this->levelNum; ++i) {
        this->polyLayers[i].Normalize(this->patOrder);
        tempNum(i) = this->polyLayers[i].lpNum;
    }
    //find the max of tempNum;
    unsigned int maxSize = tempNum.maxCoeff();
    //Build new layerPats for polylayer
    unsigned int j = 0;
    std::vector<LayerPattern*> newlayerPats;
    while (j<maxSize) {
        newlayerPats.push_back(this->patOrder[(int)std::fmod(j,this->patOrder.size())]);
        ++j;
    }
    //Build patNums and offsetAngles array
    Eigen::ArrayXXi patNums = Eigen::ArrayXXi::Zero(this->levelNum, maxSize);
    Eigen::ArrayXXd offsetAngles = Eigen::ArrayXXd::Zero(this->levelNum, maxSize);
    //Load patNums and offsetAngles of each polylayer to the two arrays
    for (unsigned int i=0; i<this->levelNum; ++i) {
        patNums.block(i, 0, 1, this->polyLayers[i].lpNum) = this->polyLayers[i].patNums.transpose();
        offsetAngles.block(i, 0, 1, this->polyLayers[i].lpNum) = this->polyLayers[i].offsetAngles.transpose();
    }
    //Interpolation
    LinearInterp lipNum(this->levels, patNums.cast<double>());
    LinearInterp lipAngle(this->levels, offsetAngles);
    Eigen::ArrayXXi newPatNums = (lipNum.Inter(newZ)).round().cast<int>();
    Eigen::ArrayXXd newOffsetAngles = lipAngle.Inter(newZ);
    //Rebuild the Region
    this->levels = newZ;
    this->levelNum = newZ.rows();
    this->polyLayers.clear();
    for (unsigned int i=0; i< this->levelNum; ++i) {
        this->polyLayers.push_back(PolyLayer(this->label, this->tag, newlayerPats, newPatNums.row(i), newOffsetAngles.row(i)));
        this->polyLayers[i].Trim();
    }
}
