#ifndef JSONIO_H
#define JSONIO_H

#include <string>
#include <utility>
#include <vector>

#include <Dense>
#include "rapidjson/document.h"

class JsonIO
{
public:
    JsonIO();
    ~JsonIO();

    void LoadJson(std::string);

    std::string bName;
    std::vector<std::string> regNames;
    Eigen::ArrayXi regMesh, webInd;
    Eigen::ArrayXd webRange;
    double radiusMesh, webMesh;


};

#endif // JSONIO_H
