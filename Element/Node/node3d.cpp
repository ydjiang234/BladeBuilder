#include "node3d.h"

Node3D::Node3D() {}

Node3D::Node3D(double X, double Y, double Z)
{
    this->coordNum = 3;
    this->data << X, Y, Z;
}

Node3D::~Node3D() {}
