#ifndef JSONIO_H
#define JSONIO_H

#include <string>
#include <utility>
#include <vector>

#include <Dense>
#include "rapidjson/document.h"
#include "profilemember.h"
#include "materialmember.h"
#include "patternmember.h"
#include "compmember.h"
#include "layupmember.h"

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
    unsigned int radiusMesh, webMesh;
    std::vector<ProfileMember> profiles;
    std::vector<MaterialMember> materials;
    std::vector<PatternMember> patterns;
    std::vector<LayupMember> layups;


};

#endif // JSONIO_H
