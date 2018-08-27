#include "layupmember.h"

LayupMember::LayupMember() {}

LayupMember::LayupMember(std::string name, std::vector<CompMember> comps) :
    Member (name)
{
    this->comps = comps;
}

LayupMember::~LayupMember() {}

void LayupMember::setData(std::string name, std::vector<CompMember> comps)
{
    this->name = name;
    this->comps = comps;
}

void LayupMember::getData(std::string* name1, std::vector<CompMember>* comps1)
{
    *name1 = this->name;
    *comps1 = this->comps;
}
