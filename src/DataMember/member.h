#ifndef MEMBER_H
#define MEMBER_H

#include <string>

class Member
{
public:
    Member();
    Member(std::string name);
    ~Member();

    std::string name;

};

#endif // MEMBER_H
