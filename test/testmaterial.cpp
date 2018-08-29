#include <iostream>
#include <iostream>
#include <vector>
#include <string>

#include <Dense>
#include "rapidjson/document.h"
#include "jsonio.h"
#include "EArrayIO.h"

#include "node.h"
#include "noderow.h"
#include "nodearray.h"
#include "linesegement.h"
#include "profilesp.h"
#include "profilemember.h"
#include "element.h"
#include "quad4.h"
#include "material.h"
#include "materialmember.h"
#include "layupmember.h"
#include "layerpattern.h"
#include "polylayer.h"
//#include "regionlayup.h"
#include "compmember.h"
#include "patternmember.h"

using namespace std;
using Eigen::ArrayXd;
using Eigen::ArrayXi;
using Eigen::ArrayXXd;
using Eigen::ArrayXXi;
using Eigen::ArrayX2d;
using Eigen::ArrayX3d;
using Eigen::Array3d;

Material* FindMat(vector<Material*> matList, string matName)
{
    Material* out;
    for (unsigned int i=0; i<matList.size(); ++i) {
        if (matList[i]->label==matName) {
            out = matList[i];
            break;
        }
    }
    return out;
}

LayerPattern* FindLP(vector<LayerPattern*> LPs, string LPName)
{
    LayerPattern* out;
    for (unsigned int i=0; i<LPs.size(); ++i) {
        if (LPs[i]->label==LPName) {
            out = LPs[i];
            break;
        }
    }
    return out;
}

int main()
{
#ifdef WIN_NUIG
    string sp = "C:/Users/0122172s/Documents/GitHub/CPP/BladeBuilder";
#elif MAC_JYD
    string sp = "/Users/JYD/Documents/Git/CPP/BladeBuilder";
#endif
    std::string fp =sp + "/test/Example.json";

    EArrayIO *EAIO = new EArrayIO();
    JsonIO jBlade;
    jBlade.LoadJson(fp);


    Eigen::Index profileNum = jBlade.profiles.size();
    Eigen::Index regNum = jBlade.regNames.size();

    //Get material
    vector<Material*> matList;
    //vector<Material> matPointerList;
    Material* tempMat;
    for (MaterialMember mat : jBlade.materials) {
        tempMat = new Material(mat.name, 0, mat.density, mat.others);
        matList.push_back(tempMat);
    }
    //Get layerpattern
    vector<LayerPattern*> LayerPatList;
    LayerPattern* tempPat;
    for (PatternMember pat : jBlade.patterns) {
        //Build layers
        vector<Material*> tempMats;
        for (unsigned int i=0; i<pat.matNames.size(); ++i) {
            tempMats.push_back(FindMat(matList, pat.matNames[i]));
        }
        tempPat = new LayerPattern(pat.name, 0, tempMats, pat.thicks, pat.angles, pat.intPs);
        LayerPatList.push_back(tempPat);
    }
    //Get layerpattern order

    //Build Layup of all regions
    //vector<RegionLayup> regLayupList;
    for (LayupMember curLayup : jBlade.layups) {
        //For each region build a regionlayup
        Eigen::ArrayXd tempLevels(curLayup.comps.size());
        vector<PolyLayer> tempPolyLayerList;
        for (unsigned int i=0; i<curLayup.comps.size(); ++i) {
            //For each comp layers, get level, patNames, patNums
            vector<LayerPattern*> tempLPs;
            unsigned int LPNum = curLayup.comps[i].patNums.rows();
            for (unsigned int j=0; j<LPNum; ++j) {
                //Get the LP pointers
                tempLPs.push_back(FindLP(LayerPatList, curLayup.comps[i].patNames[j]));
            }
            tempLevels(i) = curLayup.comps[i].radius;
            tempPolyLayerList.push_back(PolyLayer(curLayup.name, i, tempLPs, curLayup.comps[i].patNums, Eigen::ArrayXd::Zero(LPNum)));
        }
        //regLayupList.push_back(RegionLayup(curLayup.name, 0, tempLevels, tempPolyLayerList, LayerPatList));

    }


    cout<<"OK"<<endl;
    return 0;
}
