#include "jsonio.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

JsonIO::JsonIO() {}

JsonIO::~JsonIO() {}

void JsonIO::LoadJson(std::string fp)
{
    std::ifstream fstr(fp);
    std::stringstream ss;
    ss << fstr.rdbuf();
    rapidjson::Document doc;
    doc.Parse(ss.str().c_str());

    //Read blade parameters
    this->bName = doc["Name"].GetString();
    //RegNames
    for (unsigned int i=0; i<doc["Region Name List"].Size(); ++i) {
        regNames.push_back(doc["Region Name List"][i].GetString());
    }
    //Web Index
    this->webInd = Eigen::ArrayXi(doc["Web Index"].Size());
    for (unsigned int i=0; i<doc["Web Index"].Size(); ++i) {
        webInd(i) = doc["Web Index"][i].GetInt();
    }
    //Web Range
    this->webRange = Eigen::ArrayXd(doc["Web Range"].Size());
    for (unsigned int i=0; i<doc["Web Range"].Size(); ++i) {
        this->webRange(i) = doc["Web Range"][i].GetDouble();
    }
    //Region Mesh Number
    this->regMesh = Eigen::ArrayXi(doc["Region Mesh Number"].Size());
    for (unsigned int i=0; i<doc["Region Mesh Number"].Size(); ++i) {
        this->regMesh(i) = doc["Region Mesh Number"][i].GetInt();
    }
    //Radius Mesh Number
    this->radiusMesh = doc["Radius Mesh Number"].GetInt();
    //Web Mesh Number
    this->webMesh = doc["Web Mesh Number"].GetInt();

    //Read the Profile Data
    //
    //
    std::string tempName, tempName1;
    Eigen::ArrayXd splitLocU, splitLocL, dataX, dataY;
    Eigen::ArrayXd pros(5);
    for (unsigned int i=0; i<doc["Profile List"].Size(); ++i) {
        rapidjson::Value &tempValue = doc["Profile List"][i];
        //profile name
        tempName = tempValue["Name"].GetString();
        //profile properties
        pros << tempValue["Radius"].GetDouble(), tempValue["Chord Length"].GetDouble(), tempValue["Twist Angle"].GetDouble() * M_PI / 180, tempValue["x Offset"].GetDouble(), tempValue["y Offset"].GetDouble();
        //splitLoc
        splitLocU = Eigen::ArrayXd(tempValue["Split Location Upper"].Size());
        for (unsigned int i=0; i<tempValue["Split Location Upper"].Size(); ++i) {
            splitLocU(i) = tempValue["Split Location Upper"][i].GetDouble();
        }
        splitLocL = Eigen::ArrayXd(tempValue["Split Location Lower"].Size());
        for (unsigned int i=0; i<tempValue["Split Location Lower"].Size(); ++i) {
            splitLocL(i) = tempValue["Split Location Lower"][i].GetDouble();
        }
        //Data
        dataX = Eigen::ArrayXd(tempValue["DataX"].Size());
        dataY = Eigen::ArrayXd(tempValue["DataY"].Size());
        for (unsigned int i=0; i<tempValue["DataX"].Size(); ++i) {
            dataX(i) = tempValue["DataX"][i].GetDouble();
            dataY(i) = tempValue["DataY"][i].GetDouble();
        }
        this->profiles.push_back(ProfileMember(tempName, pros, splitLocU, splitLocL, dataX, dataY));
    }

    //Read Material Data
    //
    //
    double density;
    Eigen::ArrayXd others(9);
    for (rapidjson::Value& v : doc["Material List"].GetArray()) {
        //Iter all materials
        //For each material, get the Name, density and others
        tempName = v["Name"].GetString();
        density = v["Density"].GetDouble();
        //Others
        for (unsigned int i=0; i<v["Others"].Size(); ++i) {
            others(i) = v["Others"][i].GetDouble();
        }
        //Push a material member
        this->materials.push_back(MaterialMember(tempName, density, others));
    }

    //Read material patterns
    //
    //
    std::vector<std::string> matNames;
    for (rapidjson::Value& v : doc["Layer Pattern List"].GetArray()) {
        //Iter all the patterns
        //For each pattern get the name, materials, thicks, intPs, angles
        matNames.clear();
        tempName = v["Name"].GetString();
        //Materials, thicks, intPs, angles
        Eigen::ArrayXd thicks(v["Thickness"].Size());
        Eigen::ArrayXi intPs(v["Thickness"].Size());
        Eigen::ArrayXd angles(v["Thickness"].Size());
        for (unsigned int i=0; i<v["Thickness"].Size(); ++i){
            matNames.push_back(v["Materials"][i].GetString());
            thicks(i) = v["Thickness"][i].GetDouble();
            intPs(i) = v["Int Point"][i].GetInt();
            angles(i) = v["Angle"][i].GetDouble();
        }
        //Push a pattern member
        this->patterns.push_back(PatternMember(tempName, matNames, thicks, intPs, angles));
    }

    //Read Layups
    double radius;
    std::vector<std::string> patNames;
    std::vector<CompMember> comps;
    Eigen::ArrayXi patNums;
    for (rapidjson::Value& v : doc["Region Layup List"].GetArray()) {
        //Iter the layups
        tempName = v["Region Name"].GetString();
        //For each layup, iter its complayers at each radius
        for (rapidjson::Value& v1 : v["Layups"].GetArray()){
            patNames.clear();
            tempName1 = "temp";
            //For each comp, get the radius, patternNames and patterNums
            radius = v1["Radius"].GetDouble();
            patNums = Eigen::ArrayXi(v1["Patterns"].Size());
            for (unsigned int i=0; i<v1["Patterns"].Size(); ++i) {
                patNames.push_back(v1["Patterns"][i].GetString());
                patNums(i) = v1["Numbers"][i].GetInt();
            }
            comps.push_back(CompMember(tempName1, radius, patNames, patNums));
        }
        this->layups.push_back(LayupMember(tempName, comps));
    }
}
