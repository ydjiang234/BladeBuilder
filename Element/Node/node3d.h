#ifndef NODE3D_H
#define NODE3D_H

#include "node.h"
#include <iostream>
#include <Dense>

class Node3D : private Node
{
public:
    Node3D();
    Node3D(double X, double Y, double Z);
    ~Node3D();

};

#endif // NODE3D_H
