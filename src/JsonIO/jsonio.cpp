#include "jsonio.h"
#include <fstream>
#include <sstream>
#include <vector>

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
}
