#include "node3d.h"

Node3D::Node3D() : Node() {}

Node3D::Node3D(std::string label, unsigned int tag, double X, double Y, double Z) :
    Node(label, tag)
{
    this->coordNum = 3;
    this->data = Eigen::Vector3d(X, Y, Z);
}

Node3D::~Node3D() {}
