#include <iostream>
#include <vector>
#include <string>

#include <Dense>
#include "EArrayIO.h"
#include "interp.h"
#include "linearinterp.h"
#include "steffenspline.h"

using namespace std;
using Eigen::ArrayXd;
using Eigen::ArrayXXd;
using Eigen::ArrayX2d;

int main(int argc, char *argv[])
{
    EArrayIO *EAIO = new EArrayIO();

#ifdef WIN_NUIG
    string sp = "C:/Users/0122172s/Documents/GitHub/CPP/BladeBuilder";
#elif MAC_JYD
    string sp = "/Users/JYD/Documents/Git/CPP/BladeBuilder";
#endif

    string fp = sp + "/test/Interp_source.txt";
    ArrayXXd data = EAIO->loadtxt(fp);


    SteffenSpline interp1(data.col(0), data);
    
    //ArrayXXd out = interp1.Inter(ArrayXd::LinSpaced(100, 0, 25));
    //EAIO->savetxt(out, "/Users/JYD/Documents/Git/CPP/BladeBuilder/test/Interp_out.txt");
    
    cout<<"OK"<<endl;
    return 0;
}
