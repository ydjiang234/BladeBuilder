#ifndef LAYUPMEMBER_H
#define LAYUPMEMBER_H

#include <string>
#include <vector>

#include <Dense>
#include "member.h"
#include "compmember.h"

class LayupMember : public Member
{
public:
    LayupMember();
    LayupMember(std::string name, std::vector<CompMember> comps);
    ~LayupMember();

    void setData(std::string name, std::vector<CompMember> comps);
    void getData(std::string* name1, std::vector<CompMember>* comps1);

    std::vector<CompMember> comps;
};

#endif // LAYUPMEMBER_H
