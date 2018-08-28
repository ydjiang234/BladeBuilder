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
#include "layer.h"
#include "layerpattern.h"
#include "polylayer.h"
#include "regionlayup.h"
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

Material* FindMat(vector<Material> matList, string matName)
{
    Material* out;
    for (Material mat : matList) {
        if (mat.label==matName) {
            out = &mat;
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
    vector<Material> matList;
    for (MaterialMember mat : jBlade.materials) {
        matList.push_back(Material(mat.name, 0, mat.density, mat.others));
    }
    //Get layerpattern
    vector<LayerPattern> LayerPatList;
    vector<Layer> tempLayers;
    for (PatternMember pat : jBlade.patterns) {
        tempLayers.clear();
        //Build layers
        for (unsigned int i=0; i<pat.matNames.size(); ++i) {
            tempLayers.push_back(Layer("test", 0, FindMat(matList, pat.matNames[i]), pat.thicks(i), pat.angles(i), pat.intPs(i)));
        }
        LayerPatList.push_back(LayerPattern(pat.name, 0, tempLayers));
    }
    cout<<LayerPatList[0].layers[0].mat->density<<endl;


    cout<<"OK"<<endl;
    return 0;
}
