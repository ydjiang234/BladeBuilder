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


    cout<<"OK"<<endl;
    return 0;
}
