#include "blade.h"
#include "profilesp.h"

//std::cout<<"OK"<<std::endl;

Blade::Blade() {}

Blade::Blade(std::string label, unsigned int tag, JsonIO jBlade) :
    EmptyObject (label, tag)
{
    this->jBlade = jBlade;
    this->regNames = jBlade.regNames;
    this->regNum = this->regNames.size();
    this->webInd = jBlade.webInd;
    this->webNum = this->webInd.rows();
    this->webMesh = jBlade.webMesh;
    this->webRange = jBlade.webRange;
    this->bladeRange(0) = jBlade.profiles[0].pros(0);
    this->bladeRange(1) = jBlade.profiles.back().pros(0);
    this->bladeLen = this->bladeRange(1) - this->bladeRange(0);
    this->newZ = Eigen::ArrayXd::LinSpaced((int)(this->bladeLen / jBlade.radiusMesh), this->bladeRange(0), this->bladeRange(1));

    this->regMesh = Eigen::ArrayXXi(jBlade.profiles.size(), this->regNum);
    for (unsigned int i=0; i<jBlade.profiles.size(); ++i) {
        this->regMesh.row(i) = jBlade.regMesh;
    }

    this->BuildSurfNodeEleArray();
    this->BuildWebNodeEleArray();
    this->BuildMat();
    this->BuildLayerPat();
    this->BuildRegionLayup();
}

Blade::~Blade() {}

void Blade::BuildSurfNodeEleArray()
{
    Eigen::Index profileNum = this->jBlade.profiles.size();
    std::vector<NodeRow> noderows;
    Eigen::ArrayXXi keyInd(profileNum, this->regNum*2-1);
    //Build profile
    ProfileMember item;
    for (unsigned int i=0; i<profileNum; ++i) {
        item = this->jBlade.profiles[i];
        Eigen::Array3d leadCoord(3);
        leadCoord << item.pros(3), item.pros(4), item.pros(0);
        Eigen::ArrayX2d data(item.dataX.rows(), 2);
        data.col(0) = item.dataX;
        data.col(1) = item.dataY;
        ProfileSp tempProfile(item.name, data, item.pros(1), leadCoord, item.pros(2), item.splitLocU, item.splitLocL);
        std::pair<LineSegement, Eigen::ArrayXi> out;
        out = tempProfile.getData(this->regMesh.row(i), this->regMesh.row(i));
        noderows.push_back(NodeRow("test", 0, out.first.toNodes(item.pros(0))));
        keyInd.row(i) = out.second;
    }
    NodeArray na("Surface Node Array", 0, noderows, keyInd, true);
    this->surfNodeArray = na.Interp(this->newZ);
    this->surfEleArray = this->surfNodeArray.buildEleArray();
    //Build web
}

void Blade::BuildWebNodeEleArray()
{
    this->webNodeArrays = this->surfNodeArray.buildWebNodeArray(this->webInd, NodeArray::getRangeInd(this->newZ, this->webRange), this->webMesh);
    for (unsigned int i=0; i<this->webNum; ++i) {
        this->webEleArrays.push_back(this->webNodeArrays[i].buildEleArray());
    }
}

void Blade::BuildMat()
{
    //Get material
    Material* tempMat;
    MaterialMember mat;
    for (unsigned int i=0; i<this->jBlade.materials.size(); ++i) {
        mat = this->jBlade.materials[i];
        tempMat = new Material(mat.name, i, mat.density, mat.others);
        this->mats.push_back(tempMat);
    }
}

void Blade::BuildLayerPat()
{
    LayerPattern* tempPat;
    PatternMember pat;
    for (unsigned int i=0; i<this->jBlade.patterns.size(); ++i) {
        pat = this->jBlade.patterns[i];
        //Build layers
        std::vector<Material*> tempMats;
        for (unsigned int i=0; i<pat.matNames.size(); ++i) {
            tempMats.push_back(this->FindFromList<Material>(this->mats, pat.matNames[i]));
        }
        tempPat = new LayerPattern(pat.name, i, tempMats, pat.thicks, pat.angles, pat.intPs);
        this->layerPats.push_back(tempPat);
    }
}

void Blade::BuildRegionLayup()
{
    LayupMember curLayup;
    for (unsigned int i=0; i<this->jBlade.layups.size(); ++i) {
        curLayup = this->jBlade.layups[i];
        //For each region build a regionlayup
        Eigen::ArrayXd tempLevels(curLayup.comps.size());
        std::vector<PolyLayer> tempPolyLayerList;
        for (unsigned int i=0; i<curLayup.comps.size(); ++i) {
            //For each comp layers, get level, patNames, patNums
            std::vector<LayerPattern*> tempLPs;
            unsigned int LPNum = curLayup.comps[i].patNums.rows();
            for (unsigned int j=0; j<LPNum; ++j) {
                //Get the LP pointers
                tempLPs.push_back(this->FindFromList<LayerPattern>(this->layerPats, curLayup.comps[i].patNames[j]));
            }
            tempLevels(i) = curLayup.comps[i].radius;
            tempPolyLayerList.push_back(PolyLayer(curLayup.name, i, tempLPs, curLayup.comps[i].patNums, Eigen::ArrayXd::Zero(LPNum)));
        }
        this->regLayups.push_back(RegionLayup(curLayup.name, 0, tempLevels, tempPolyLayerList, this->layerPats));

    }

    for (unsigned int i=0; i<this->regLayups.size(); ++i) {
        this->regLayups[i].Iterp(this->newZ);
    }
}

template <class T>
T* Blade::FindFromList(std::vector<T*> inputList, std::string target)
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
