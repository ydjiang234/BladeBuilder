#include <iostream>
#include <vector>
#include <string>

#include <Dense>
#include "EArrayIO.h"
#include "interp.h"


using namespace std;
using Eigen::ArrayXd;
using Eigen::ArrayXXd;
using Eigen::ArrayX2d;

int main(int argc, char *argv[])
{
    EArrayIO *EAIO = new EArrayIO();

#ifdef WIN_NUIG
    string sp = "C:/Users/0122172s/Documents/GitHub/CPP/BladeBuilder";
#else
    string sp = "/Git/CPP/BladeBuilder";
#endif

    string fp = sp + "/test/Interp_source.txt";
    ArrayXXd data = EAIO->loadtxt(fp);


    Interp interp1(data.col(0), data);

    cout<<"OK"<<endl;
    return 0;
}
