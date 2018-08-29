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
#include "regionlayup.h"
#include "compmember.h"
#include "patternmember.h"
#include "blade.h"

using namespace std;
using Eigen::ArrayXd;
using Eigen::ArrayXi;
using Eigen::ArrayXXd;
using Eigen::ArrayXXi;
using Eigen::ArrayX2d;
using Eigen::ArrayX3d;
using Eigen::Array3d;

template <class T>
T* FindFromList(std::vector<T*> inputList, std::string target)
{
    T* out;
    for (unsigned int i=0; i<inputList.size(); ++i) {
        if (inputList[i]->label==target) {
            out = inputList[i];
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

    Blade blade("test", 0, jBlade);

    /*


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
            tempMats.push_back(FindFromList<Material>(matList, pat.matNames[i]));
        }
        tempPat = new LayerPattern(pat.name, 0, tempMats, pat.thicks, pat.angles, pat.intPs);
        LayerPatList.push_back(tempPat);
    }
    //Get layerpattern order

    //Build Layup of all regions
    vector<RegionLayup> regLayupList;
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
                tempLPs.push_back(FindFromList<LayerPattern>(LayerPatList, curLayup.comps[i].patNames[j]));
            }
            tempLevels(i) = curLayup.comps[i].radius;
            tempPolyLayerList.push_back(PolyLayer(curLayup.name, i, tempLPs, curLayup.comps[i].patNums, Eigen::ArrayXd::Zero(LPNum)));
        }
        regLayupList.push_back(RegionLayup(curLayup.name, 0, tempLevels, tempPolyLayerList, LayerPatList));

    }

    for (unsigned int i=0; i<regLayupList.size(); ++i) {
        regLayupList[i].Iterp(Eigen::ArrayXd::LinSpaced(100,0,8450));
    }
    cout<<regLayupList[2].polyLayers[0].patNums<<endl;
    */

    cout<<"OK"<<endl;
    return 0;
}
