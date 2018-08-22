#ifndef NODE_H
#define NODE_H

#include <string>
#include <Dense>
#include "emptyobject.h"

class Node : public EmptyObject
{
public:
    Node();
    Node(std::string label, unsigned int tag);
    ~Node();

    unsigned int coordNum;
    Eigen::VectorXd data;

};

#endif // NODE_H
