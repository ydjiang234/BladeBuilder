#include <iostream>
#include <iostream>
#include <vector>
#include <string>

#include <Dense>
#include "rapidjson/document.h"
#include "jsonio.h"
#include "materialmember.h"

using namespace std;
using Eigen::ArrayXi;
using Eigen::ArrayXd;
using Eigen::ArrayXXd;
using Eigen::ArrayX2d;
#include <Dense>
#include "EArrayIO.h"
#include "node.h"
#include "noderow.h"
#include "nodearray.h"
#include "linesegement.h"

using namespace std;
using Eigen::ArrayXd;
using Eigen::ArrayXXd;
using Eigen::ArrayX2d;

int main()
{
    std::string fp = "c:/Users/0122172s/Google Drive/BladeComp/GUI/Example.json";

    JsonIO JIO;
    JIO.LoadJson(fp);
    EArrayIO *EAIO = new EArrayIO();

#ifdef WIN_NUIG
    string sp = "C:/Users/0122172s/Documents/GitHub/CPP/BladeBuilder";
#elif MAC_JYD
    string sp = "/Users/JYD/Documents/Git/CPP/BladeBuilder";
#endif
    
    cout<<"OK"<<endl;
    return 0;
}
