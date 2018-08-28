#include "polylayer.h"
#include <cmath>

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

void PolyLayer::Normalize(std::vector<LayerPattern*> patOrder)
{
    unsigned int orderNum = patOrder.size();
    std::vector<LayerPattern*> newLayerPats;
    Eigen::ArrayXi newPatNums = Eigen::ArrayXi::Zero(orderNum * this->lpNum);
    Eigen::ArrayXd newOffsetAngles = Eigen::ArrayXi::Zero(orderNum * this->lpNum);
    unsigned int iPat = 0;
    unsigned int jOrder = 0;
    LayerPattern* curLP;
    while (iPat<this->lpNum) {
        curLP = patOrder[(unsigned int)std::fmod(jOrder, orderNum)];
        newLayerPats.push_back(curLP);
        if (this->layerPats[iPat]==curLP) {
            newPatNums(jOrder) = this->patNums(iPat);
            newOffsetAngles(jOrder) = this->offsetAngles(iPat);
            ++iPat;
        }
        ++jOrder;
    }
    //Reduce the newPatNums, newOffsetAngles' size to jOrder (!!not jOrder-1 as jOrder starts from 0)
    this->layerPats = newLayerPats;
    this->lpNum = this->layerPats.size();
    this->patNums = newPatNums.head(this->lpNum);
    this->offsetAngles = newOffsetAngles.head(this->lpNum);
}

void PolyLayer::Trim()
{
    unsigned int curInd;
    for (unsigned int i=lpNum; i>=0; --i) {
        if (this->patNums(i)>0) {
            curInd = i;
            break;
        }
    }
    std::vector<LayerPattern*> newLayerPats(&this->layerPats[0], &this->layerPats[curInd]);
    Eigen::ArrayXi newPatNums = this->patNums.head(curInd+1);
    Eigen::ArrayXd newOffsetAngles = this->offsetAngles.head(curInd+1);
    this->layerPats = newLayerPats;
    this->patNums = newPatNums;
    this->offsetAngles = newOffsetAngles;
    this->lpNum = this->layerPats.size();
}
