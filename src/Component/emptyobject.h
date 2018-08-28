#ifndef EMPTYOBJECT_H
#define EMPTYOBJECT_H

#include <string>

class EmptyObject
{
public:
    EmptyObject();
    EmptyObject(std::string label, unsigned int tag);
    ~EmptyObject();

    void reTag(unsigned int tag);

    std::string label;
    unsigned int tag;
};

#endif // EMPTYOBJECT_H
