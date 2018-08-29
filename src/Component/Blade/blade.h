#ifndef BLADE_H
#define BLADE_H

#include <vector>

#include <Dense>
#include "emptyobject.h"
#include "jsonio.h"
#include "material.h"
#include "regionlayup.h"
#include "layerpattern.h"
#include "nodearray.h"
#include "elementarray.h"

class Blade : public EmptyObject
{
public:
    Blade();
    Blade(std::string label, unsigned int tag, JsonIO jBlade);
    ~Blade();

    JsonIO jBlade;

    std::vector<std::string> regNames;
    unsigned int regNum, webNum, webMesh;
    double bladeLen;
    Eigen::ArrayXi webInd;
    Eigen::Array2d webRang, bladeRange;
    Eigen::ArrayXd newZ;
    Eigen::ArrayXXi regMesh;

    NodeArray surfNodeArray;
    std::vector<NodeArray> webNodeArrays;
    ElementArray surfEleArray;
    std::vector<ElementArray> webEleArrays;

    std::vector<Material*> mats;
    std::vector<LayerPattern*> layerPats;
    std::vector<RegionLayup> regLayups;

private:
    void BuildSurfNodeEleArray();
    void BuildWebNodeEleArray();
    void BuildMat();
    void BuildLayerPat();
    void BuildRegionLayup();
    template <class T>
    static T* FindFromList(std::vector<T*> inputList, std::string target);


};

#endif // BLADE_H
