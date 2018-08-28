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

using namespace std;
using Eigen::ArrayXd;
using Eigen::ArrayXi;
using Eigen::ArrayXXd;
using Eigen::ArrayXXi;
using Eigen::ArrayX2d;
using Eigen::ArrayX3d;
using Eigen::Array3d;

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
    vector<NodeRow> noderows;
    ArrayXXi keyInd(profileNum, regNum*2-1);
    //Build profile
    unsigned int i = 0;
    for (ProfileMember item : jBlade.profiles) {
        Array3d leadCoord(3);
        leadCoord << item.pros(3), item.pros(4), item.pros(0);
        ArrayX2d data(item.dataX.rows(), 2);
        data.col(0) = item.dataX;
        data.col(1) = item.dataY;
        ProfileSp tempProfile(item.name, data, item.pros(1), leadCoord, item.pros(2), item.splitLocU, item.splitLocL);
        std::pair<LineSegement, Eigen::ArrayXi> out;
        out = tempProfile.getData(jBlade.regMesh, jBlade.regMesh);
        noderows.push_back(NodeRow("test", 0, out.first.toNodes(item.pros(0))));
        keyInd.row(i) = out.second;
        ++i;
    }
    NodeArray na("test", 0, noderows, keyInd, true);
    NodeArray na1 = na.Interp(ArrayXd::LinSpaced(50, 0, 8450));
    na1.setTag(1);
    ElementArray ea = na1.buildEleArray();
    ea.setTag(1);


    ArrayX3d out = na1.getNodeCoords();
    EAIO->savetxt(out, sp+"/test/AllNodes.txt");
    cout<<"OK"<<endl;
    return 0;
}
