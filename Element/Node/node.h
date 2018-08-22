#ifndef NODE_H
#define NODE_H

#include <string>
#include <Dense>

class Node
{
public:
    Node();
    Node(std::string label, unsigned int tag);
    ~Node();

    unsigned int coordNum;
    Eigen::VectorXd data;
    std::string label;
    unsigned int tag;

};

#endif // NODE_H
